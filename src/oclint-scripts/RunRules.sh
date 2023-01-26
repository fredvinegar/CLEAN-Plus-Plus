#!/bin/bash

rm /tmp/Data /tmp/Methods /tmp/NumOfFanIn /tmp/NumOfFanInFunctions > /dev/null 2>&1

./../build/oclint-release/bin/oclint-json-compilation-database -p $1 -- -rule=AggregateInfo > /dev/null 2>&1
./../build/oclint-release/bin/oclint-json-compilation-database -p $1 -- -rule=MethodsInfo > /dev/null 2>&1
./../build/oclint-release/bin/oclint-json-compilation-database -p $1 -- -rule=NumOfFanIn > /dev/null 2>&1
./../build/oclint-release/bin/oclint-json-compilation-database -p $1 -- -rule=NumOfFanInFunctions > /dev/null 2>&1

./../build/oclint-release/bin/oclint-json-compilation-database -p $1 -- -rule=LazyClass -rule=SwissArmyKnife -rule=DataClass -rule=ComplexClass -rule=RefusedBequest -rule=SpaghettiCode -rule=LargeClass -rule=ClassDataShouldBePrivate -rule=GodClass -rule=SpeculativeGenerality -rule=BrainClass -rule=ImperativeAbstraction -rule=MultifacetedAbstraction -rule=UnnecessaryAbstraction -rule=UnutilizedAbstraction -rule=DeficientEncapsulation -rule=UnexploitedEncapsulation -rule=BrokenModularization -rule=InsufficientModularization -rule=HubLikeModularization -rule=DispersedCoupling -rule=IntensiveCoupling -rule=LongMethod -rule=BrainMethod -rule=LongParameterList -rule=MessageChain -rule=ShotgunSurgery -rule=AbstractFunctionCallFromConstructor -rule=ComplexConditional -rule=ComplexMethod -rule=EmptyCatchClause -rule=LongIdentifier -rule=LongStatement -rule=MagicNumber -rule=MissingDefault

rm /tmp/Data /tmp/Methods /tmp/NumOfFanIn /tmp/NumOfFanInFunctions > /dev/null 2>&1