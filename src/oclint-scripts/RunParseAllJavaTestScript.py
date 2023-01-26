import os
import sys
from pathlib import Path
from subprocess import Popen
from collections import Counter

import pandas as pd
from tqdm import tqdm
projects_list = ['AbstractFunctionCallFromConstructorTest', 'ComplexMethodTest', 'GodClassTest', 'LongIdentifierTest',
                 'MultifacetedAbstractionTest', 'UnnecessaryAbstractionTest', 'BrainClassTest',
                 'HubLikeModularizationTest', 'LongMethodTest', 'RefusedBequestTest', 'UnutilizedAbstractionTest',
                 'BrainMethodTest', 'DataClassTest', 'ImperativeAbstractionTest', 'LongParameterListTest',
                 'ShotgunSurgeryTest', 'BrokenModularizationTest', 'DeficientEncapsulationTest',
                 'InsufficientModularizationTest', 'LongStatementTest', 'SpaghettiCodeTest',
                 'ClassDataShouldBePrivateTest', 'DispersedCouplingTest', 'IntensiveCouplingTest', 'MagicNumberTest',
                 'SpeculativeGeneralityTest','ComplexClassTest', 'EmptyCatchClauseTest', 'LargeClassTest',
                 'MessageChainTest', 'SwissArmyKnifeTest', 'ComplexConditionalTest', 'LazyClassTest',
                 'MissingDefaultTest', 'UnexploitedEncapsulationTest']

in_path = sys.argv[1]
out_path = Path("/", "tmp", "TestCases")
out_path.mkdir(exist_ok=True, parents=True)
cwd = os.path.dirname(os.path.realpath(__file__))

results = list()
for project_name in tqdm(projects_list):
    try:

        cmd = ["java", "-jar", Path(cwd, "DesigniteJava_Organic.jar"), "-i", f"{in_path}/{project_name}", "-o", Path(out_path,project_name)]
        with open(os.devnull, "w") as fp:
            Popen(cmd, stdout=fp)


        df1 = pd.read_csv(Path(out_path, project_name, "designCodeSmells.csv"))
        df2 = pd.read_csv(Path(out_path, project_name, "implementationCodeSmells.csv"))
        df3 = pd.read_csv(Path(out_path, project_name, "organicMethodCodeSmells.csv"))
        df4 = pd.read_csv(Path(out_path, project_name, "organicTypeCodeSmells.csv"))

        df = pd.concat([df1, df2, df3, df4], axis=0)

        smells_list = list(df['Code Smell'])
        smells_list = [s.title() for s in smells_list]
        smells_dict = Counter(smells_list)

        fields_names = ["Lazy Class", "Swiss Army Knife", "Data Class",
                        "Complex Class", "Refused Bequest", "Spaghetti Code", "Large Class", "Class Data Should Be Private",
                        "God Class", "Speculative Generality",
                        "Brain Class", "Imperative Abstraction", "Multifaceted Abstraction", "Unnecessary Abstraction",
                        "Unutilized Abstraction", "Deficient Encapsulation", "Unexploited Encapsulation",
                        "Broken Modularization", "Insufficient Modularization", "Hub Like Modularization", "Dispersed Coupling",
                        "Intensive Coupling", "Long Method", "Brain Method", "Long Parameter List", "Message Chain",
                        "Shotgun Surgery", "Abstract Function Call From Constructor", "Complex Conditional", "Complex Method",
                        "Empty Catch Clause", "Long Identifier", "Long Statement", "Magic Number", "Missing Default"]
        smells_dict = {k: smells_dict[k] for k in fields_names}
        data_dict = {"Project": project_name, 'Total Code Smells': sum(smells_dict.values()),
                     'Total Types of Code Smells': len([x for x, y in smells_dict.items() if y > 0])}
        df_a = pd.DataFrame(data_dict, columns=["Project", "Total Code Smells", "Total Types of Code Smells"], index=[0])
        df_b = pd.DataFrame(smells_dict, columns=fields_names, index=[0])
        df_final = pd.concat([df_a, df_b], axis=1)
        results.append(df_final)
    except (Exception):
        print(f'The project: {project_name} failed!')
    pd.concat(results, axis=0).to_csv("java_results_test.csv", index=False)


