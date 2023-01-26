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

for project in projects_list:
    print(f'cd /tests-cpp/{project}; rm -f compile-command.json; make clean; bear make')

