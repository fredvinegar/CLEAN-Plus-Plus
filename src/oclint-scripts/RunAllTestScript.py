
from pathlib import Path

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

reports_path = Path("/oclint-repo/oclint-scripts/TestsReports")
reports_path.mkdir(exist_ok=True, parents=True)

for project in projects_list:

    print(f'/oclint-repo/oclint-scripts/RunRules.sh /tests-cpp/{project}/ > /oclint-repo/oclint-scripts/TestsReports/{project}_report.txt')

