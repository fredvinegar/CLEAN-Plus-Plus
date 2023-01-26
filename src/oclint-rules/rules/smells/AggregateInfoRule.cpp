#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/util/ASTUtil.h"
#include "oclint/util/StdUtil.h"
#include <iostream>
#include <fstream>
#include "oclint/util/ASTUtil.h"
#include <regex>
#include <list>
#include <map>
#include "clang/Lex/Lexer.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "oclint/RuleCarrier.h"
#include <algorithm>
#include "clang/Lex/Lexer.h"


using namespace std;
using namespace clang;
using namespace oclint;
clang::LangOptions lo;


class AggregateInfoRule : public AbstractASTVisitorRule<AggregateInfoRule>
{
private:
    std::fstream file;
    list<string> allClasses;


public:
    virtual const string name() const override
    {
        return "aggregate info";
    }

    virtual int priority() const override
    {
        return 1;
    }

    virtual const string category() const override
    {
        return "smells";
    }

#ifdef DOCGEN
    virtual const std::string since() const override
    {
        return "0.6";
    }

    virtual const std::string description() const override
    {
        return "Description...";
    }

    virtual const std::string example() const override
    {
        return R"rst(
.. code-block:: cpp

    class Foo
    {
    public:
        int x;
        float y;

    }
        )rst";
    }

//    virtual const std::map<std::string, std::string> thresholds() const override
//    {
//        std::map<std::string, std::string> thresholdMapping;
//        thresholdMapping["AGGREGATE_INFO_RULE"] =
//            "agg.";
//        return thresholdMapping;
//    }
#endif

    virtual void setUp() override
    {

    }



    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        string className = decl->getNameAsString();
        bool isClass = decl->isClass();
        bool hasDefinition = decl->hasDefinition();
//        cout << "class name: " <<className << " has " << decl->hasDefinition() << endl;
        if (std::find((this->allClasses).begin(), (this->allClasses).end(), className) != (this->allClasses).end()){
            return true;
        }
        (this->allClasses).push_back(className);
        file.open ("/tmp/Data",std::ios::app);
        if ( !file.is_open() ){
            cout << "no file" << endl;
        }

        int methodCount = distance(decl->method_begin(), decl->method_end());
//        for (auto i = decl->method_begin() ; i != decl->method_end() ; i++){
//            string n = (*i)->getNameAsString();
//            bool v = (*i)->isVirtual();
//        }
        int length = getNumLineOfClass(decl);
        bool isAbstract = false;
        if (hasDefinition && isClass){
            isAbstract = decl->isAbstract();

        }

        file << className << ";" << isAbstract << ";" << length << ";" << methodCount << ";";
        string allBases = "";
        if (hasDefinition && isClass){
            for (auto b = decl->bases_begin() ; b != decl->bases_end() ; b++ ){
                string name = (b->getType()).getAsString();
                name.erase(name.begin(), name.begin()+6);
                if (allBases == ""){
                    allBases.append(name);
                } else {
                    allBases.append(" ");
                    allBases.append(name);
                }
            }
        }
        string allMethods = "";
        int wmc = 0;
        for (auto m = decl->method_begin() ; m != decl->method_end() ; m++ ){
            string name = m->getNameAsString();
            if (allMethods == ""){
                allMethods.append(name);
            } else {
                allMethods.append(" ");
                allMethods.append(name);
            }

            wmc += calculateCyclomaticComplexityOfMethod(*m);
        }
        file << allBases << ";" << allMethods << ";" << getTCC(decl) << ";" << wmc << "\n";


        file.close();

        return false;
    }

    float getTCC(CXXRecordDecl *decl){
        list<string> fields;
        map<string,list<string>> methodsFieldsMap;
        clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
        string regex_begin = "[^a-zA-Z0-9]";
        for (auto f = decl->field_begin() ; f != decl->field_end() ; f++ ){
            fields.push_back((*f)->getNameAsString());
        }
        int numOfMethods =0;

        for (auto f = decl->method_begin() ; f != decl->method_end() ; f++ ){
            string methodName = f->getNameAsString();
            list<string> fieldsInMethods;
            Stmt *funcBody = (*f)->getBody();
            if (funcBody == 0){
                continue;
            }
            numOfMethods ++ ;
            SourceRange range = funcBody->getSourceRange();
//            SourceLocation b = range.getBegin();
//            SourceLocation e = range.getEnd();
//            FullSourceLoc fsl = FullSourceLoc(b,*TheSourceMgr);
//            const char *c = fsl.getCharacterData();

//            char *c = const_cast<char *>(TheSourceMgr->getCharacterData(b));
            auto start_loc = TheSourceMgr->getSpellingLoc(range.getBegin());
            auto last_token_loc = TheSourceMgr->getSpellingLoc(range.getEnd());
            auto end_loc = clang::Lexer::getLocForEndOfToken(last_token_loc, 0, *TheSourceMgr, lo);
            auto printable_range = clang::SourceRange{start_loc, end_loc};
            string text = get_source_text_raw(printable_range, *TheSourceMgr);
            for (auto field = fields.begin() ; field != fields.end() ; field++ ){
                string theRegex = regex_begin + *field + regex_begin;
                if (regex_search(text , regex(theRegex))){
                    fieldsInMethods.push_back(*field);
                }
            }
            methodsFieldsMap.insert({methodName , fieldsInMethods});
        }

        int connected = 0 ;

        map<string,list<string>>::iterator m;
        map<string,list<string>>::iterator n;


        for (m = methodsFieldsMap.begin() ; m != methodsFieldsMap.end() ; m++ ){
            for (n = m ; n != methodsFieldsMap.end() ; n++){
                if (n == m){
                    continue;
                }
                if (hasCommon(m->second , n->second)){
                    connected ++;
                }
            }
        }

        float np = static_cast< float >(numOfMethods*(numOfMethods-1)/2);
        float TCC = static_cast< float >(connected)/np;
        if (np == 0){
            return 0;
        }
        return TCC;
    }

    bool hasCommon (list<string> l1 , list <string> l2){
        for (auto i = l1.begin() ; i != l1.end() ; i++){
            for (auto j = l2.begin() ; j != l2.end() ; j++){
                if ((*i) == (*j)){
                    return true;
                }
            }
        }
        return false;
    }
    int calculateCyclomaticComplexityOfMethod(FunctionDecl *decl){
        Stmt *theStmt = decl->getBody();
        if (theStmt == 0 ){
            return 0;
        }
        clang::SourceManager *TheSourceMgr = &_carrier->getSourceManager();
        SourceRange range = theStmt->getSourceRange();
        SourceLocation b = range.getBegin();
        SourceLocation e = range.getEnd();
        FullSourceLoc fsl = FullSourceLoc(b,*TheSourceMgr);

        auto start_loc = TheSourceMgr->getSpellingLoc(range.getBegin());
        auto last_token_loc = TheSourceMgr->getSpellingLoc(range.getEnd());
        auto end_loc = clang::Lexer::getLocForEndOfToken(last_token_loc, 0, *TheSourceMgr, lo);
        auto printable_range = clang::SourceRange{start_loc, end_loc};

        string method_text = get_source_text_raw(printable_range, *TheSourceMgr);
        method_text = cleanCommentsFromCodeText(method_text);

        return 1 + countStringInMethod(method_text, "if") + countStringInMethod(method_text, "while") + countStringInMethod(method_text, "for") + countStringInMethod(method_text, "case");
    }

    int countStringInMethod (string method_text, string str){
        string regex_begin = "[^a-zA-Z0-9]";
        string theRegex = regex_begin + str + regex_begin;
        if (regex_search(method_text , regex(theRegex))){
            regex re(theRegex);
            auto words_begin = std::sregex_iterator(method_text.begin(), method_text.end(), re);
            auto words_end = std::sregex_iterator();
            return distance(words_begin, words_end);
        } else return 0;

    }

    string cleanCommentsFromCodeText(string origin){
        string delimiter1 = "//";
        string delimiter2 = "\n";
        string delimiter3 = "/*";
        string delimiter4 = "*/";
        size_t pos1 = 0;
        size_t pos2 = 0;
        size_t pos3 = 0;
        size_t pos4 = 0;
        while ((pos1 = origin.find(delimiter1)) != string::npos){
            pos2 = origin.find(delimiter2,pos1);
            origin.erase(pos1,pos2-pos1);
        }
        while ((pos3 = origin.find(delimiter3)) != string::npos){
            pos4 = origin.find(delimiter4,pos3);
            origin.erase(pos3,pos4-pos3);
        }
        return origin;
    }

    std::string get_source_text_raw(clang::SourceRange range, const clang::SourceManager& sm) {
        return (clang::Lexer::getSourceText(clang::CharSourceRange::getCharRange(range), sm, clang::LangOptions())).str();}

    int getNumLineOfClass(CXXRecordDecl *decl)
    {
        int numLine = 2;
        numLine += distance(decl->field_begin(), decl->field_end());
        for (auto method = decl->method_begin() ; method != decl->method_end() ; method++ ){
            Stmt *stmt = method->getBody();
            if  (stmt == 0 ) {
                continue;
            }
            const int lineCount = getLineCount(stmt->getSourceRange(), _carrier->getSourceManager());
            numLine += lineCount;


        }
        return numLine;
    }

};

static RuleSet rules(new AggregateInfoRule());
