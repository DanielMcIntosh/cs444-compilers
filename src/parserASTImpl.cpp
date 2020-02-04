#include "parserASTBase.h"
#ifndef PARSERAST_DISABLED
#include "parserAST.h"
#include "parserNode.h"

namespace Parse { 

using namespace std;

// Goal -> BOF CompilationUnit EOF 
void parserASTGoal_BOFCompilationUnitEof(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::CompilationUnit);
  auto t = new TreeGoal;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTGoalVariants::BOFCompilationUnitEof;
  t->compilationUnit = dynamic_cast<TreeCompilationUnit *>((*stack)[n - 1]);
  assert(t->compilationUnit);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> IntegerLiteral 
void parserASTLiteral_IntegerLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::IntegerLiteral);
  auto t = new TreeLiteral;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTLiteralVariants::IntegerLiteral;
  t->integerLiteral = dynamic_cast<TreeIntegerLiteral *>((*stack)[n - 1]);
  assert(t->integerLiteral);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> BooleanLiteral 
void parserASTLiteral_BooleanLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::BooleanLiteral);
  auto t = new TreeLiteral;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTLiteralVariants::BooleanLiteral;
  t->booleanLiteral = dynamic_cast<TreeBooleanLiteral *>((*stack)[n - 1]);
  assert(t->booleanLiteral);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> CharacterLiteral 
void parserASTLiteral_CharacterLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::CharacterLiteral);
  auto t = new TreeLiteral;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTLiteralVariants::CharacterLiteral;
  t->characterLiteral = dynamic_cast<TreeCharacterLiteral *>((*stack)[n - 1]);
  assert(t->characterLiteral);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> StringLiteral 
void parserASTLiteral_StringLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StringLiteral);
  auto t = new TreeLiteral;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTLiteralVariants::StringLiteral;
  t->stringLiteral = dynamic_cast<TreeStringLiteral *>((*stack)[n - 1]);
  assert(t->stringLiteral);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> NullLiteral 
void parserASTLiteral_NullLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::NullLiteral);
  auto t = new TreeLiteral;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTLiteralVariants::NullLiteral;
  t->nullLiteral = dynamic_cast<TreeNullLiteral *>((*stack)[n - 1]);
  assert(t->nullLiteral);
  stack->pop_back();
  stack->push_back(t);
}

// Type -> PrimitiveType 
void parserASTType_PrimitiveType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimitiveType);
  auto t = new TreeType;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTTypeVariants::PrimitiveType;
  t->primitiveType = dynamic_cast<TreePrimitiveType *>((*stack)[n - 1]);
  assert(t->primitiveType);
  stack->pop_back();
  stack->push_back(t);
}

// Type -> ReferenceType 
void parserASTType_ReferenceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ReferenceType);
  auto t = new TreeType;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTTypeVariants::ReferenceType;
  t->referenceType = dynamic_cast<TreeReferenceType *>((*stack)[n - 1]);
  assert(t->referenceType);
  stack->pop_back();
  stack->push_back(t);
}

// PrimitiveType -> boolean 
void parserASTPrimitiveType_boolean(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreePrimitiveType;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTPrimitiveTypeVariants::boolean;
  stack->push_back(t);
}

// PrimitiveType -> byte 
void parserASTPrimitiveType_byte(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreePrimitiveType;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTPrimitiveTypeVariants::byte;
  stack->push_back(t);
}

// PrimitiveType -> short 
void parserASTPrimitiveType_Short(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreePrimitiveType;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTPrimitiveTypeVariants::Short;
  stack->push_back(t);
}

// PrimitiveType -> int 
void parserASTPrimitiveType_Int(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreePrimitiveType;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTPrimitiveTypeVariants::Int;
  stack->push_back(t);
}

// PrimitiveType -> char 
void parserASTPrimitiveType_Char(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreePrimitiveType;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTPrimitiveTypeVariants::Char;
  stack->push_back(t);
}

// ReferenceType -> ClassOrInterfaceType 
void parserASTReferenceType_ClassOrInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassOrInterfaceType);
  auto t = new TreeReferenceType;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTReferenceTypeVariants::ClassOrInterfaceType;
  t->classOrInterfaceType = dynamic_cast<TreeClassOrInterfaceType *>((*stack)[n - 1]);
  assert(t->classOrInterfaceType);
  stack->pop_back();
  stack->push_back(t);
}

// ReferenceType -> ArrayType 
void parserASTReferenceType_ArrayType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayType);
  auto t = new TreeReferenceType;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTReferenceTypeVariants::ArrayType;
  t->arrayType = dynamic_cast<TreeArrayType *>((*stack)[n - 1]);
  assert(t->arrayType);
  stack->pop_back();
  stack->push_back(t);
}

// ClassOrInterfaceType -> Name 
void parserASTClassOrInterfaceType_Name(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TreeClassOrInterfaceType;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTClassOrInterfaceTypeVariants::Name;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// ClassType -> ClassOrInterfaceType 
void parserASTClassType_ClassOrInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassOrInterfaceType);
  auto t = new TreeClassType;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTClassTypeVariants::ClassOrInterfaceType;
  t->classOrInterfaceType = dynamic_cast<TreeClassOrInterfaceType *>((*stack)[n - 1]);
  assert(t->classOrInterfaceType);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceType -> ClassOrInterfaceType 
void parserASTInterfaceType_ClassOrInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassOrInterfaceType);
  auto t = new TreeInterfaceType;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTInterfaceTypeVariants::ClassOrInterfaceType;
  t->classOrInterfaceType = dynamic_cast<TreeClassOrInterfaceType *>((*stack)[n - 1]);
  assert(t->classOrInterfaceType);
  stack->pop_back();
  stack->push_back(t);
}

// ArrayType -> PrimitiveType [ ] 
void parserASTArrayType_PrimitiveTypeLSBrRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimitiveType);
  auto t = new TreeArrayType;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTArrayTypeVariants::PrimitiveTypeLSBrRSBr;
  t->primitiveType = dynamic_cast<TreePrimitiveType *>((*stack)[n - 1]);
  assert(t->primitiveType);
  stack->pop_back();
  stack->push_back(t);
}

// ArrayType -> Name [ ] 
void parserASTArrayType_NameLSBrRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TreeArrayType;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTArrayTypeVariants::NameLSBrRSBr;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// Name -> Identifier 
void parserASTName_Identifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TreeName;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTNameVariants::Identifier;
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->push_back(t);
}

// Name -> Name . Identifier 
void parserASTName_NameDotIdentifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Name);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TreeName;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTNameVariants::NameDotIdentifier;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 2]);
  assert(t->name);
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> 
void parserASTCompilationUnit_(vector<Tree *> *stack) {
}

// CompilationUnit -> PackageDeclaration 
void parserASTCompilationUnit_PackageDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PackageDeclaration);
  auto t = new TreeCompilationUnit;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTCompilationUnitVariants::PackageDeclaration;
  t->packageDeclaration = dynamic_cast<TreePackageDeclaration *>((*stack)[n - 1]);
  assert(t->packageDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> ImportDeclarations 
void parserASTCompilationUnit_ImportDeclarations(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclarations);
  auto t = new TreeCompilationUnit;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTCompilationUnitVariants::ImportDeclarations;
  t->importDeclarations = dynamic_cast<TreeImportDeclarations *>((*stack)[n - 1]);
  assert(t->importDeclarations);
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> PackageDeclaration ImportDeclarations 
void parserASTCompilationUnit_PackageDeclarationImportDeclarations(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PackageDeclaration);
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclarations);
  auto t = new TreeCompilationUnit;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTCompilationUnitVariants::PackageDeclarationImportDeclarations;
  t->packageDeclaration = dynamic_cast<TreePackageDeclaration *>((*stack)[n - 2]);
  assert(t->packageDeclaration);
  t->importDeclarations = dynamic_cast<TreeImportDeclarations *>((*stack)[n - 1]);
  assert(t->importDeclarations);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> TypeDeclaration 
void parserASTCompilationUnit_TypeDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclaration);
  auto t = new TreeCompilationUnit;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTCompilationUnitVariants::TypeDeclaration;
  t->typeDeclaration = dynamic_cast<TreeTypeDeclaration *>((*stack)[n - 1]);
  assert(t->typeDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> PackageDeclaration TypeDeclaration 
void parserASTCompilationUnit_PackageDeclarationTypeDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PackageDeclaration);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclaration);
  auto t = new TreeCompilationUnit;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTCompilationUnitVariants::PackageDeclarationTypeDeclaration;
  t->packageDeclaration = dynamic_cast<TreePackageDeclaration *>((*stack)[n - 2]);
  assert(t->packageDeclaration);
  t->typeDeclaration = dynamic_cast<TreeTypeDeclaration *>((*stack)[n - 1]);
  assert(t->typeDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> ImportDeclarations TypeDeclaration 
void parserASTCompilationUnit_ImportDeclarationsTypeDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ImportDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclaration);
  auto t = new TreeCompilationUnit;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTCompilationUnitVariants::ImportDeclarationsTypeDeclaration;
  t->importDeclarations = dynamic_cast<TreeImportDeclarations *>((*stack)[n - 2]);
  assert(t->importDeclarations);
  t->typeDeclaration = dynamic_cast<TreeTypeDeclaration *>((*stack)[n - 1]);
  assert(t->typeDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> PackageDeclaration ImportDeclarations TypeDeclaration 
void parserASTCompilationUnit_PackageDeclarationImportDeclarationsTypeDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::PackageDeclaration);
  assert((*stack)[n - 2]->type == NonTerminalType::ImportDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclaration);
  auto t = new TreeCompilationUnit;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTCompilationUnitVariants::PackageDeclarationImportDeclarationsTypeDeclaration;
  t->packageDeclaration = dynamic_cast<TreePackageDeclaration *>((*stack)[n - 3]);
  assert(t->packageDeclaration);
  t->importDeclarations = dynamic_cast<TreeImportDeclarations *>((*stack)[n - 2]);
  assert(t->importDeclarations);
  t->typeDeclaration = dynamic_cast<TreeTypeDeclaration *>((*stack)[n - 1]);
  assert(t->typeDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ImportDeclarations -> ImportDeclaration 
void parserASTImportDeclarations_ImportDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclaration);
  auto t = new TreeImportDeclarations;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTImportDeclarationsVariants::ImportDeclaration;
  t->importDeclaration = dynamic_cast<TreeImportDeclaration *>((*stack)[n - 1]);
  assert(t->importDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ImportDeclarations -> ImportDeclarations ImportDeclaration 
void parserASTImportDeclarations_ImportDeclarationsImportDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ImportDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclaration);
  auto t = new TreeImportDeclarations;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTImportDeclarationsVariants::ImportDeclarationsImportDeclaration;
  t->importDeclarations = dynamic_cast<TreeImportDeclarations *>((*stack)[n - 2]);
  assert(t->importDeclarations);
  t->importDeclaration = dynamic_cast<TreeImportDeclaration *>((*stack)[n - 1]);
  assert(t->importDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// PackageDeclaration -> package Name ; 
void parserASTPackageDeclaration_packageNameSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TreePackageDeclaration;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTPackageDeclarationVariants::packageNameSCol;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// ImportDeclaration -> SingleTypeImportDeclaration 
void parserASTImportDeclaration_SingleTypeImportDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::SingleTypeImportDeclaration);
  auto t = new TreeImportDeclaration;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTImportDeclarationVariants::SingleTypeImportDeclaration;
  t->singleTypeImportDeclaration = dynamic_cast<TreeSingleTypeImportDeclaration *>((*stack)[n - 1]);
  assert(t->singleTypeImportDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ImportDeclaration -> TypeImportOnDemandDeclaration 
void parserASTImportDeclaration_TypeImportOnDemandDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeImportOnDemandDeclaration);
  auto t = new TreeImportDeclaration;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTImportDeclarationVariants::TypeImportOnDemandDeclaration;
  t->typeImportOnDemandDeclaration = dynamic_cast<TreeTypeImportOnDemandDeclaration *>((*stack)[n - 1]);
  assert(t->typeImportOnDemandDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// SingleTypeImportDeclaration -> import Name ; 
void parserASTSingleTypeImportDeclaration_importNameSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TreeSingleTypeImportDeclaration;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTSingleTypeImportDeclarationVariants::importNameSCol;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// TypeImportOnDemandDeclaration -> import Name . * ; 
void parserASTTypeImportOnDemandDeclaration_importNameDotStarSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TreeTypeImportOnDemandDeclaration;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTTypeImportOnDemandDeclarationVariants::importNameDotStarSCol;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// TypeDeclaration -> ClassDeclaration 
void parserASTTypeDeclaration_ClassDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassDeclaration);
  auto t = new TreeTypeDeclaration;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTTypeDeclarationVariants::ClassDeclaration;
  t->classDeclaration = dynamic_cast<TreeClassDeclaration *>((*stack)[n - 1]);
  assert(t->classDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// TypeDeclaration -> InterfaceDeclaration 
void parserASTTypeDeclaration_InterfaceDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceDeclaration);
  auto t = new TreeTypeDeclaration;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTTypeDeclarationVariants::InterfaceDeclaration;
  t->interfaceDeclaration = dynamic_cast<TreeInterfaceDeclaration *>((*stack)[n - 1]);
  assert(t->interfaceDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// TypeDeclaration -> ; 
void parserASTTypeDeclaration_SCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeTypeDeclaration;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTTypeDeclarationVariants::SCol;
  stack->push_back(t);
}

// Modifiers -> Modifier 
void parserASTModifiers_Modifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifier);
  auto t = new TreeModifiers;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTModifiersVariants::Modifier;
  t->modifier = dynamic_cast<TreeModifier *>((*stack)[n - 1]);
  assert(t->modifier);
  stack->pop_back();
  stack->push_back(t);
}

// Modifiers -> Modifiers Modifier 
void parserASTModifiers_ModifiersModifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifier);
  auto t = new TreeModifiers;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTModifiersVariants::ModifiersModifier;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 2]);
  assert(t->modifiers);
  t->modifier = dynamic_cast<TreeModifier *>((*stack)[n - 1]);
  assert(t->modifier);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// Modifier -> public 
void parserASTModifier_Public(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeModifier;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTModifierVariants::Public;
  stack->push_back(t);
}

// Modifier -> protected 
void parserASTModifier_Protected(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeModifier;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTModifierVariants::Protected;
  stack->push_back(t);
}

// Modifier -> static 
void parserASTModifier_Static(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeModifier;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTModifierVariants::Static;
  stack->push_back(t);
}

// Modifier -> abstract 
void parserASTModifier_abstract(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeModifier;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTModifierVariants::abstract;
  stack->push_back(t);
}

// Modifier -> final 
void parserASTModifier_final(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeModifier;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTModifierVariants::final;
  stack->push_back(t);
}

// Modifier -> native 
void parserASTModifier_native(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeModifier;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTModifierVariants::native;
  stack->push_back(t);
}

// ClassDeclaration -> class Identifier ClassBody 
void parserASTClassDeclaration_ClassIdentifierClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTClassDeclarationVariants::ClassIdentifierClassBody;
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 1]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier ClassBody 
void parserASTClassDeclaration_ModifiersClassIdentifierClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTClassDeclarationVariants::ModifiersClassIdentifierClassBody;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 3]);
  assert(t->modifiers);
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 1]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> class Identifier extends ClassType ClassBody 
void parserASTClassDeclaration_ClassIdentifierextendsClassTypeClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassType);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTClassDeclarationVariants::ClassIdentifierextendsClassTypeClassBody;
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 3]);
  assert(t->identifier);
  t->classType = dynamic_cast<TreeClassType *>((*stack)[n - 2]);
  assert(t->classType);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 1]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier extends ClassType ClassBody 
void parserASTClassDeclaration_ModifiersClassIdentifierextendsClassTypeClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 4);
  assert((*stack)[n - 4]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 3]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassType);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  parserASTSetTopParents(stack, 4, t);
  parserASTPopulateChildrenList(t, *stack, 4);
  t->variant = NTClassDeclarationVariants::ModifiersClassIdentifierextendsClassTypeClassBody;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 4]);
  assert(t->modifiers);
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 3]);
  assert(t->identifier);
  t->classType = dynamic_cast<TreeClassType *>((*stack)[n - 2]);
  assert(t->classType);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 1]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> class Identifier implements InterfaceTypeList ClassBody 
void parserASTClassDeclaration_ClassIdentifierimplementsInterfaceTypeListClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceTypeList);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTClassDeclarationVariants::ClassIdentifierimplementsInterfaceTypeListClassBody;
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 3]);
  assert(t->identifier);
  t->interfaceTypeList = dynamic_cast<TreeInterfaceTypeList *>((*stack)[n - 2]);
  assert(t->interfaceTypeList);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 1]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier implements InterfaceTypeList ClassBody 
void parserASTClassDeclaration_ModifiersClassIdentifierimplementsInterfaceTypeListClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 4);
  assert((*stack)[n - 4]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 3]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceTypeList);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  parserASTSetTopParents(stack, 4, t);
  parserASTPopulateChildrenList(t, *stack, 4);
  t->variant = NTClassDeclarationVariants::ModifiersClassIdentifierimplementsInterfaceTypeListClassBody;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 4]);
  assert(t->modifiers);
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 3]);
  assert(t->identifier);
  t->interfaceTypeList = dynamic_cast<TreeInterfaceTypeList *>((*stack)[n - 2]);
  assert(t->interfaceTypeList);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 1]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> class Identifier extends ClassType implements InterfaceTypeList ClassBody 
void parserASTClassDeclaration_ClassIdentifierextendsClassTypeimplementsInterfaceTypeListClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 4);
  assert((*stack)[n - 4]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 3]->type == NonTerminalType::ClassType);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceTypeList);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  parserASTSetTopParents(stack, 4, t);
  parserASTPopulateChildrenList(t, *stack, 4);
  t->variant = NTClassDeclarationVariants::ClassIdentifierextendsClassTypeimplementsInterfaceTypeListClassBody;
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 4]);
  assert(t->identifier);
  t->classType = dynamic_cast<TreeClassType *>((*stack)[n - 3]);
  assert(t->classType);
  t->interfaceTypeList = dynamic_cast<TreeInterfaceTypeList *>((*stack)[n - 2]);
  assert(t->interfaceTypeList);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 1]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier extends ClassType implements InterfaceTypeList ClassBody 
void parserASTClassDeclaration_ModifiersClassIdentifierextendsClassTypeimplementsInterfaceTypeListClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 5);
  assert((*stack)[n - 5]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 4]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 3]->type == NonTerminalType::ClassType);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceTypeList);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  parserASTSetTopParents(stack, 5, t);
  parserASTPopulateChildrenList(t, *stack, 5);
  t->variant = NTClassDeclarationVariants::ModifiersClassIdentifierextendsClassTypeimplementsInterfaceTypeListClassBody;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 5]);
  assert(t->modifiers);
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 4]);
  assert(t->identifier);
  t->classType = dynamic_cast<TreeClassType *>((*stack)[n - 3]);
  assert(t->classType);
  t->interfaceTypeList = dynamic_cast<TreeInterfaceTypeList *>((*stack)[n - 2]);
  assert(t->interfaceTypeList);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 1]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceTypeList -> InterfaceType 
void parserASTInterfaceTypeList_InterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceType);
  auto t = new TreeInterfaceTypeList;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTInterfaceTypeListVariants::InterfaceType;
  t->interfaceType = dynamic_cast<TreeInterfaceType *>((*stack)[n - 1]);
  assert(t->interfaceType);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceTypeList -> InterfaceTypeList , InterfaceType 
void parserASTInterfaceTypeList_InterfaceTypeListComInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceTypeList);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceType);
  auto t = new TreeInterfaceTypeList;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTInterfaceTypeListVariants::InterfaceTypeListComInterfaceType;
  t->interfaceTypeList = dynamic_cast<TreeInterfaceTypeList *>((*stack)[n - 2]);
  assert(t->interfaceTypeList);
  t->interfaceType = dynamic_cast<TreeInterfaceType *>((*stack)[n - 1]);
  assert(t->interfaceType);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassBody -> { } 
void parserASTClassBody_LCBrRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeClassBody;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTClassBodyVariants::LCBrRCBr;
  stack->push_back(t);
}

// ClassBody -> { ClassMemberDeclarations } 
void parserASTClassBody_LCBrClassMemberDeclarationsRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassMemberDeclarations);
  auto t = new TreeClassBody;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTClassBodyVariants::LCBrClassMemberDeclarationsRCBr;
  t->classMemberDeclarations = dynamic_cast<TreeClassMemberDeclarations *>((*stack)[n - 1]);
  assert(t->classMemberDeclarations);
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclarations -> ClassMemberDeclaration 
void parserASTClassMemberDeclarations_ClassMemberDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassMemberDeclaration);
  auto t = new TreeClassMemberDeclarations;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTClassMemberDeclarationsVariants::ClassMemberDeclaration;
  t->classMemberDeclaration = dynamic_cast<TreeClassMemberDeclaration *>((*stack)[n - 1]);
  assert(t->classMemberDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclarations -> ClassMemberDeclarations ClassMemberDeclaration 
void parserASTClassMemberDeclarations_ClassMemberDeclarationsClassMemberDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassMemberDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassMemberDeclaration);
  auto t = new TreeClassMemberDeclarations;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTClassMemberDeclarationsVariants::ClassMemberDeclarationsClassMemberDeclaration;
  t->classMemberDeclarations = dynamic_cast<TreeClassMemberDeclarations *>((*stack)[n - 2]);
  assert(t->classMemberDeclarations);
  t->classMemberDeclaration = dynamic_cast<TreeClassMemberDeclaration *>((*stack)[n - 1]);
  assert(t->classMemberDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclaration -> FieldDeclaration 
void parserASTClassMemberDeclaration_FieldDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FieldDeclaration);
  auto t = new TreeClassMemberDeclaration;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTClassMemberDeclarationVariants::FieldDeclaration;
  t->fieldDeclaration = dynamic_cast<TreeFieldDeclaration *>((*stack)[n - 1]);
  assert(t->fieldDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclaration -> MethodDeclaration 
void parserASTClassMemberDeclaration_MethodDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclaration);
  auto t = new TreeClassMemberDeclaration;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTClassMemberDeclarationVariants::MethodDeclaration;
  t->methodDeclaration = dynamic_cast<TreeMethodDeclaration *>((*stack)[n - 1]);
  assert(t->methodDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclaration -> ConstructorDeclaration 
void parserASTClassMemberDeclaration_ConstructorDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ConstructorDeclaration);
  auto t = new TreeClassMemberDeclaration;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTClassMemberDeclarationVariants::ConstructorDeclaration;
  t->constructorDeclaration = dynamic_cast<TreeConstructorDeclaration *>((*stack)[n - 1]);
  assert(t->constructorDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// FieldDeclaration -> Type VariableDeclarator ; 
void parserASTFieldDeclaration_TypeVariableDeclaratorSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableDeclarator);
  auto t = new TreeFieldDeclaration;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTFieldDeclarationVariants::TypeVariableDeclaratorSCol;
  t->type = dynamic_cast<TreeType *>((*stack)[n - 2]);
  assert(t->type);
  t->variableDeclarator = dynamic_cast<TreeVariableDeclarator *>((*stack)[n - 1]);
  assert(t->variableDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// FieldDeclaration -> Modifiers Type VariableDeclarator ; 
void parserASTFieldDeclaration_ModifiersTypeVariableDeclaratorSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableDeclarator);
  auto t = new TreeFieldDeclaration;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTFieldDeclarationVariants::ModifiersTypeVariableDeclaratorSCol;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 3]);
  assert(t->modifiers);
  t->type = dynamic_cast<TreeType *>((*stack)[n - 2]);
  assert(t->type);
  t->variableDeclarator = dynamic_cast<TreeVariableDeclarator *>((*stack)[n - 1]);
  assert(t->variableDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// VariableDeclarator -> Identifier 
void parserASTVariableDeclarator_Identifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TreeVariableDeclarator;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTVariableDeclaratorVariants::Identifier;
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->push_back(t);
}

// VariableDeclarator -> Identifier = Expression 
void parserASTVariableDeclarator_IdentifierEqExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreeVariableDeclarator;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTVariableDeclaratorVariants::IdentifierEqExpression;
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodDeclaration -> MethodHeader MethodBody 
void parserASTMethodDeclaration_MethodHeaderMethodBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::MethodHeader);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodBody);
  auto t = new TreeMethodDeclaration;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTMethodDeclarationVariants::MethodHeaderMethodBody;
  t->methodHeader = dynamic_cast<TreeMethodHeader *>((*stack)[n - 2]);
  assert(t->methodHeader);
  t->methodBody = dynamic_cast<TreeMethodBody *>((*stack)[n - 1]);
  assert(t->methodBody);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> Type MethodDeclarator 
void parserASTMethodHeader_TypeMethodDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclarator);
  auto t = new TreeMethodHeader;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTMethodHeaderVariants::TypeMethodDeclarator;
  t->type = dynamic_cast<TreeType *>((*stack)[n - 2]);
  assert(t->type);
  t->methodDeclarator = dynamic_cast<TreeMethodDeclarator *>((*stack)[n - 1]);
  assert(t->methodDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> Modifiers Type MethodDeclarator 
void parserASTMethodHeader_ModifiersTypeMethodDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclarator);
  auto t = new TreeMethodHeader;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTMethodHeaderVariants::ModifiersTypeMethodDeclarator;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 3]);
  assert(t->modifiers);
  t->type = dynamic_cast<TreeType *>((*stack)[n - 2]);
  assert(t->type);
  t->methodDeclarator = dynamic_cast<TreeMethodDeclarator *>((*stack)[n - 1]);
  assert(t->methodDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> void MethodDeclarator 
void parserASTMethodHeader_VoidMethodDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclarator);
  auto t = new TreeMethodHeader;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTMethodHeaderVariants::VoidMethodDeclarator;
  t->methodDeclarator = dynamic_cast<TreeMethodDeclarator *>((*stack)[n - 1]);
  assert(t->methodDeclarator);
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> Modifiers void MethodDeclarator 
void parserASTMethodHeader_ModifiersVoidMethodDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclarator);
  auto t = new TreeMethodHeader;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTMethodHeaderVariants::ModifiersVoidMethodDeclarator;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 2]);
  assert(t->modifiers);
  t->methodDeclarator = dynamic_cast<TreeMethodDeclarator *>((*stack)[n - 1]);
  assert(t->methodDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodDeclarator -> Identifier ( ) 
void parserASTMethodDeclarator_IdentifierLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TreeMethodDeclarator;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTMethodDeclaratorVariants::IdentifierLParRPar;
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->push_back(t);
}

// MethodDeclarator -> Identifier ( FormalParameterList ) 
void parserASTMethodDeclarator_IdentifierLParFormalParameterListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameterList);
  auto t = new TreeMethodDeclarator;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTMethodDeclaratorVariants::IdentifierLParFormalParameterListRPar;
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->formalParameterList = dynamic_cast<TreeFormalParameterList *>((*stack)[n - 1]);
  assert(t->formalParameterList);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// FormalParameterList -> FormalParameter 
void parserASTFormalParameterList_FormalParameter(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameter);
  auto t = new TreeFormalParameterList;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTFormalParameterListVariants::FormalParameter;
  t->formalParameter = dynamic_cast<TreeFormalParameter *>((*stack)[n - 1]);
  assert(t->formalParameter);
  stack->pop_back();
  stack->push_back(t);
}

// FormalParameterList -> FormalParameterList , FormalParameter 
void parserASTFormalParameterList_FormalParameterListComFormalParameter(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::FormalParameterList);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameter);
  auto t = new TreeFormalParameterList;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTFormalParameterListVariants::FormalParameterListComFormalParameter;
  t->formalParameterList = dynamic_cast<TreeFormalParameterList *>((*stack)[n - 2]);
  assert(t->formalParameterList);
  t->formalParameter = dynamic_cast<TreeFormalParameter *>((*stack)[n - 1]);
  assert(t->formalParameter);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// FormalParameter -> Type Identifier 
void parserASTFormalParameter_TypeIdentifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TreeFormalParameter;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTFormalParameterVariants::TypeIdentifier;
  t->type = dynamic_cast<TreeType *>((*stack)[n - 2]);
  assert(t->type);
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodBody -> Block 
void parserASTMethodBody_Block(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Block);
  auto t = new TreeMethodBody;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTMethodBodyVariants::Block;
  t->block = dynamic_cast<TreeBlock *>((*stack)[n - 1]);
  assert(t->block);
  stack->pop_back();
  stack->push_back(t);
}

// MethodBody -> AbstractMethodBody 
void parserASTMethodBody_AbstractMethodBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AbstractMethodBody);
  auto t = new TreeMethodBody;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTMethodBodyVariants::AbstractMethodBody;
  t->abstractMethodBody = dynamic_cast<TreeAbstractMethodBody *>((*stack)[n - 1]);
  assert(t->abstractMethodBody);
  stack->pop_back();
  stack->push_back(t);
}

// AbstractMethodBody -> ; 
void parserASTAbstractMethodBody_SCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeAbstractMethodBody;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTAbstractMethodBodyVariants::SCol;
  stack->push_back(t);
}

// ConstructorDeclaration -> ConstructorDeclarator Block 
void parserASTConstructorDeclaration_ConstructorDeclaratorBlock(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ConstructorDeclarator);
  assert((*stack)[n - 1]->type == NonTerminalType::Block);
  auto t = new TreeConstructorDeclaration;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTConstructorDeclarationVariants::ConstructorDeclaratorBlock;
  t->constructorDeclarator = dynamic_cast<TreeConstructorDeclarator *>((*stack)[n - 2]);
  assert(t->constructorDeclarator);
  t->block = dynamic_cast<TreeBlock *>((*stack)[n - 1]);
  assert(t->block);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ConstructorDeclaration -> Modifiers ConstructorDeclarator Block 
void parserASTConstructorDeclaration_ModifiersConstructorDeclaratorBlock(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::ConstructorDeclarator);
  assert((*stack)[n - 1]->type == NonTerminalType::Block);
  auto t = new TreeConstructorDeclaration;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTConstructorDeclarationVariants::ModifiersConstructorDeclaratorBlock;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 3]);
  assert(t->modifiers);
  t->constructorDeclarator = dynamic_cast<TreeConstructorDeclarator *>((*stack)[n - 2]);
  assert(t->constructorDeclarator);
  t->block = dynamic_cast<TreeBlock *>((*stack)[n - 1]);
  assert(t->block);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ConstructorDeclarator -> Identifier ( ) 
void parserASTConstructorDeclarator_IdentifierLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TreeConstructorDeclarator;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTConstructorDeclaratorVariants::IdentifierLParRPar;
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->push_back(t);
}

// ConstructorDeclarator -> Identifier ( FormalParameterList ) 
void parserASTConstructorDeclarator_IdentifierLParFormalParameterListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameterList);
  auto t = new TreeConstructorDeclarator;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTConstructorDeclaratorVariants::IdentifierLParFormalParameterListRPar;
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->formalParameterList = dynamic_cast<TreeFormalParameterList *>((*stack)[n - 1]);
  assert(t->formalParameterList);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> interface Identifier InterfaceBody 
void parserASTInterfaceDeclaration_interfaceIdentifierInterfaceBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceBody);
  auto t = new TreeInterfaceDeclaration;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTInterfaceDeclarationVariants::interfaceIdentifierInterfaceBody;
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->interfaceBody = dynamic_cast<TreeInterfaceBody *>((*stack)[n - 1]);
  assert(t->interfaceBody);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> Modifiers interface Identifier InterfaceBody 
void parserASTInterfaceDeclaration_ModifiersinterfaceIdentifierInterfaceBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceBody);
  auto t = new TreeInterfaceDeclaration;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTInterfaceDeclarationVariants::ModifiersinterfaceIdentifierInterfaceBody;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 3]);
  assert(t->modifiers);
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->interfaceBody = dynamic_cast<TreeInterfaceBody *>((*stack)[n - 1]);
  assert(t->interfaceBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> interface Identifier ExtendsInterfaces InterfaceBody 
void parserASTInterfaceDeclaration_interfaceIdentifierExtendsInterfacesInterfaceBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 2]->type == NonTerminalType::ExtendsInterfaces);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceBody);
  auto t = new TreeInterfaceDeclaration;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTInterfaceDeclarationVariants::interfaceIdentifierExtendsInterfacesInterfaceBody;
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 3]);
  assert(t->identifier);
  t->extendsInterfaces = dynamic_cast<TreeExtendsInterfaces *>((*stack)[n - 2]);
  assert(t->extendsInterfaces);
  t->interfaceBody = dynamic_cast<TreeInterfaceBody *>((*stack)[n - 1]);
  assert(t->interfaceBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> Modifiers interface Identifier ExtendsInterfaces InterfaceBody 
void parserASTInterfaceDeclaration_ModifiersinterfaceIdentifierExtendsInterfacesInterfaceBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 4);
  assert((*stack)[n - 4]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 3]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 2]->type == NonTerminalType::ExtendsInterfaces);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceBody);
  auto t = new TreeInterfaceDeclaration;
  parserASTSetTopParents(stack, 4, t);
  parserASTPopulateChildrenList(t, *stack, 4);
  t->variant = NTInterfaceDeclarationVariants::ModifiersinterfaceIdentifierExtendsInterfacesInterfaceBody;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 4]);
  assert(t->modifiers);
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 3]);
  assert(t->identifier);
  t->extendsInterfaces = dynamic_cast<TreeExtendsInterfaces *>((*stack)[n - 2]);
  assert(t->extendsInterfaces);
  t->interfaceBody = dynamic_cast<TreeInterfaceBody *>((*stack)[n - 1]);
  assert(t->interfaceBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ExtendsInterfaces -> extends InterfaceType 
void parserASTExtendsInterfaces_extendsInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceType);
  auto t = new TreeExtendsInterfaces;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTExtendsInterfacesVariants::extendsInterfaceType;
  t->interfaceType = dynamic_cast<TreeInterfaceType *>((*stack)[n - 1]);
  assert(t->interfaceType);
  stack->pop_back();
  stack->push_back(t);
}

// ExtendsInterfaces -> ExtendsInterfaces , InterfaceType 
void parserASTExtendsInterfaces_ExtendsInterfacesComInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ExtendsInterfaces);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceType);
  auto t = new TreeExtendsInterfaces;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTExtendsInterfacesVariants::ExtendsInterfacesComInterfaceType;
  t->extendsInterfaces = dynamic_cast<TreeExtendsInterfaces *>((*stack)[n - 2]);
  assert(t->extendsInterfaces);
  t->interfaceType = dynamic_cast<TreeInterfaceType *>((*stack)[n - 1]);
  assert(t->interfaceType);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceBody -> { } 
void parserASTInterfaceBody_LCBrRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeInterfaceBody;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTInterfaceBodyVariants::LCBrRCBr;
  stack->push_back(t);
}

// InterfaceBody -> { InterfaceMemberDeclarations } 
void parserASTInterfaceBody_LCBrInterfaceMemberDeclarationsRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceMemberDeclarations);
  auto t = new TreeInterfaceBody;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTInterfaceBodyVariants::LCBrInterfaceMemberDeclarationsRCBr;
  t->interfaceMemberDeclarations = dynamic_cast<TreeInterfaceMemberDeclarations *>((*stack)[n - 1]);
  assert(t->interfaceMemberDeclarations);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceMemberDeclarations -> InterfaceMemberDeclaration 
void parserASTInterfaceMemberDeclarations_InterfaceMemberDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceMemberDeclaration);
  auto t = new TreeInterfaceMemberDeclarations;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTInterfaceMemberDeclarationsVariants::InterfaceMemberDeclaration;
  t->interfaceMemberDeclaration = dynamic_cast<TreeInterfaceMemberDeclaration *>((*stack)[n - 1]);
  assert(t->interfaceMemberDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceMemberDeclarations -> InterfaceMemberDeclarations InterfaceMemberDeclaration 
void parserASTInterfaceMemberDeclarations_InterfaceMemberDeclarationsInterfaceMemberDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceMemberDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceMemberDeclaration);
  auto t = new TreeInterfaceMemberDeclarations;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTInterfaceMemberDeclarationsVariants::InterfaceMemberDeclarationsInterfaceMemberDeclaration;
  t->interfaceMemberDeclarations = dynamic_cast<TreeInterfaceMemberDeclarations *>((*stack)[n - 2]);
  assert(t->interfaceMemberDeclarations);
  t->interfaceMemberDeclaration = dynamic_cast<TreeInterfaceMemberDeclaration *>((*stack)[n - 1]);
  assert(t->interfaceMemberDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceMemberDeclaration -> AbstractMethodDeclaration 
void parserASTInterfaceMemberDeclaration_AbstractMethodDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AbstractMethodDeclaration);
  auto t = new TreeInterfaceMemberDeclaration;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTInterfaceMemberDeclarationVariants::AbstractMethodDeclaration;
  t->abstractMethodDeclaration = dynamic_cast<TreeAbstractMethodDeclaration *>((*stack)[n - 1]);
  assert(t->abstractMethodDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// AbstractMethodDeclaration -> MethodHeader ; 
void parserASTAbstractMethodDeclaration_MethodHeaderSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodHeader);
  auto t = new TreeAbstractMethodDeclaration;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTAbstractMethodDeclarationVariants::MethodHeaderSCol;
  t->methodHeader = dynamic_cast<TreeMethodHeader *>((*stack)[n - 1]);
  assert(t->methodHeader);
  stack->pop_back();
  stack->push_back(t);
}

// Block -> { } 
void parserASTBlock_LCBrRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeBlock;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTBlockVariants::LCBrRCBr;
  stack->push_back(t);
}

// Block -> { BlockStatements } 
void parserASTBlock_LCBrBlockStatementsRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::BlockStatements);
  auto t = new TreeBlock;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTBlockVariants::LCBrBlockStatementsRCBr;
  t->blockStatements = dynamic_cast<TreeBlockStatements *>((*stack)[n - 1]);
  assert(t->blockStatements);
  stack->pop_back();
  stack->push_back(t);
}

// BlockStatements -> BlockStatement 
void parserASTBlockStatements_BlockStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::BlockStatement);
  auto t = new TreeBlockStatements;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTBlockStatementsVariants::BlockStatement;
  t->blockStatement = dynamic_cast<TreeBlockStatement *>((*stack)[n - 1]);
  assert(t->blockStatement);
  stack->pop_back();
  stack->push_back(t);
}

// BlockStatements -> BlockStatements BlockStatement 
void parserASTBlockStatements_BlockStatementsBlockStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::BlockStatements);
  assert((*stack)[n - 1]->type == NonTerminalType::BlockStatement);
  auto t = new TreeBlockStatements;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTBlockStatementsVariants::BlockStatementsBlockStatement;
  t->blockStatements = dynamic_cast<TreeBlockStatements *>((*stack)[n - 2]);
  assert(t->blockStatements);
  t->blockStatement = dynamic_cast<TreeBlockStatement *>((*stack)[n - 1]);
  assert(t->blockStatement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// BlockStatement -> LocalVariableDeclarationStatement 
void parserASTBlockStatement_LocalVariableDeclarationStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::LocalVariableDeclarationStatement);
  auto t = new TreeBlockStatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTBlockStatementVariants::LocalVariableDeclarationStatement;
  t->localVariableDeclarationStatement = dynamic_cast<TreeLocalVariableDeclarationStatement *>((*stack)[n - 1]);
  assert(t->localVariableDeclarationStatement);
  stack->pop_back();
  stack->push_back(t);
}

// BlockStatement -> Statement 
void parserASTBlockStatement_Statement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TreeBlockStatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTBlockStatementVariants::Statement;
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->push_back(t);
}

// LocalVariableDeclarationStatement -> LocalVariableDeclaration ; 
void parserASTLocalVariableDeclarationStatement_LocalVariableDeclarationSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::LocalVariableDeclaration);
  auto t = new TreeLocalVariableDeclarationStatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTLocalVariableDeclarationStatementVariants::LocalVariableDeclarationSCol;
  t->localVariableDeclaration = dynamic_cast<TreeLocalVariableDeclaration *>((*stack)[n - 1]);
  assert(t->localVariableDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// LocalVariableDeclaration -> Type VariableDeclarator 
void parserASTLocalVariableDeclaration_TypeVariableDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableDeclarator);
  auto t = new TreeLocalVariableDeclaration;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTLocalVariableDeclarationVariants::TypeVariableDeclarator;
  t->type = dynamic_cast<TreeType *>((*stack)[n - 2]);
  assert(t->type);
  t->variableDeclarator = dynamic_cast<TreeVariableDeclarator *>((*stack)[n - 1]);
  assert(t->variableDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> StatementWithoutTrailingSubstatement 
void parserASTStatement_StatementWithoutTrailingSubstatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementWithoutTrailingSubstatement);
  auto t = new TreeStatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementVariants::StatementWithoutTrailingSubstatement;
  t->statementWithoutTrailingSubstatement = dynamic_cast<TreeStatementWithoutTrailingSubstatement *>((*stack)[n - 1]);
  assert(t->statementWithoutTrailingSubstatement);
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> IfThenStatement 
void parserASTStatement_IfThenStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::IfThenStatement);
  auto t = new TreeStatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementVariants::IfThenStatement;
  t->ifThenStatement = dynamic_cast<TreeIfThenStatement *>((*stack)[n - 1]);
  assert(t->ifThenStatement);
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> IfThenElseStatement 
void parserASTStatement_IfThenElseStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::IfThenElseStatement);
  auto t = new TreeStatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementVariants::IfThenElseStatement;
  t->ifThenElseStatement = dynamic_cast<TreeIfThenElseStatement *>((*stack)[n - 1]);
  assert(t->ifThenElseStatement);
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> WhileStatement 
void parserASTStatement_WhileStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::WhileStatement);
  auto t = new TreeStatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementVariants::WhileStatement;
  t->whileStatement = dynamic_cast<TreeWhileStatement *>((*stack)[n - 1]);
  assert(t->whileStatement);
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> ForStatement 
void parserASTStatement_ForStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ForStatement);
  auto t = new TreeStatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementVariants::ForStatement;
  t->forStatement = dynamic_cast<TreeForStatement *>((*stack)[n - 1]);
  assert(t->forStatement);
  stack->pop_back();
  stack->push_back(t);
}

// StatementNoShortIf -> StatementWithoutTrailingSubstatement 
void parserASTStatementNoShortIf_StatementWithoutTrailingSubstatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementWithoutTrailingSubstatement);
  auto t = new TreeStatementNoShortIf;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementNoShortIfVariants::StatementWithoutTrailingSubstatement;
  t->statementWithoutTrailingSubstatement = dynamic_cast<TreeStatementWithoutTrailingSubstatement *>((*stack)[n - 1]);
  assert(t->statementWithoutTrailingSubstatement);
  stack->pop_back();
  stack->push_back(t);
}

// StatementNoShortIf -> IfThenElseStatementNoShortIf 
void parserASTStatementNoShortIf_IfThenElseStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::IfThenElseStatementNoShortIf);
  auto t = new TreeStatementNoShortIf;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementNoShortIfVariants::IfThenElseStatementNoShortIf;
  t->ifThenElseStatementNoShortIf = dynamic_cast<TreeIfThenElseStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->ifThenElseStatementNoShortIf);
  stack->pop_back();
  stack->push_back(t);
}

// StatementNoShortIf -> WhileStatementNoShortIf 
void parserASTStatementNoShortIf_WhileStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::WhileStatementNoShortIf);
  auto t = new TreeStatementNoShortIf;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementNoShortIfVariants::WhileStatementNoShortIf;
  t->whileStatementNoShortIf = dynamic_cast<TreeWhileStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->whileStatementNoShortIf);
  stack->pop_back();
  stack->push_back(t);
}

// StatementNoShortIf -> ForStatementNoShortIf 
void parserASTStatementNoShortIf_ForStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ForStatementNoShortIf);
  auto t = new TreeStatementNoShortIf;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementNoShortIfVariants::ForStatementNoShortIf;
  t->forStatementNoShortIf = dynamic_cast<TreeForStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->forStatementNoShortIf);
  stack->pop_back();
  stack->push_back(t);
}

// StatementWithoutTrailingSubstatement -> Block 
void parserASTStatementWithoutTrailingSubstatement_Block(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Block);
  auto t = new TreeStatementWithoutTrailingSubstatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementWithoutTrailingSubstatementVariants::Block;
  t->block = dynamic_cast<TreeBlock *>((*stack)[n - 1]);
  assert(t->block);
  stack->pop_back();
  stack->push_back(t);
}

// StatementWithoutTrailingSubstatement -> EmptyStatement 
void parserASTStatementWithoutTrailingSubstatement_EmptyStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::EmptyStatement);
  auto t = new TreeStatementWithoutTrailingSubstatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementWithoutTrailingSubstatementVariants::EmptyStatement;
  t->emptyStatement = dynamic_cast<TreeEmptyStatement *>((*stack)[n - 1]);
  assert(t->emptyStatement);
  stack->pop_back();
  stack->push_back(t);
}

// StatementWithoutTrailingSubstatement -> ExpressionStatement 
void parserASTStatementWithoutTrailingSubstatement_ExpressionStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ExpressionStatement);
  auto t = new TreeStatementWithoutTrailingSubstatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementWithoutTrailingSubstatementVariants::ExpressionStatement;
  t->expressionStatement = dynamic_cast<TreeExpressionStatement *>((*stack)[n - 1]);
  assert(t->expressionStatement);
  stack->pop_back();
  stack->push_back(t);
}

// StatementWithoutTrailingSubstatement -> ReturnStatement 
void parserASTStatementWithoutTrailingSubstatement_ReturnStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ReturnStatement);
  auto t = new TreeStatementWithoutTrailingSubstatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementWithoutTrailingSubstatementVariants::ReturnStatement;
  t->returnStatement = dynamic_cast<TreeReturnStatement *>((*stack)[n - 1]);
  assert(t->returnStatement);
  stack->pop_back();
  stack->push_back(t);
}

// EmptyStatement -> ; 
void parserASTEmptyStatement_SCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeEmptyStatement;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTEmptyStatementVariants::SCol;
  stack->push_back(t);
}

// ExpressionStatement -> StatementExpression ; 
void parserASTExpressionStatement_StatementExpressionSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementExpression);
  auto t = new TreeExpressionStatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTExpressionStatementVariants::StatementExpressionSCol;
  t->statementExpression = dynamic_cast<TreeStatementExpression *>((*stack)[n - 1]);
  assert(t->statementExpression);
  stack->pop_back();
  stack->push_back(t);
}

// StatementExpression -> Assignment 
void parserASTStatementExpression_Assignment(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Assignment);
  auto t = new TreeStatementExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementExpressionVariants::Assignment;
  t->assignment = dynamic_cast<TreeAssignment *>((*stack)[n - 1]);
  assert(t->assignment);
  stack->pop_back();
  stack->push_back(t);
}

// StatementExpression -> MethodInvocation 
void parserASTStatementExpression_MethodInvocation(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodInvocation);
  auto t = new TreeStatementExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementExpressionVariants::MethodInvocation;
  t->methodInvocation = dynamic_cast<TreeMethodInvocation *>((*stack)[n - 1]);
  assert(t->methodInvocation);
  stack->pop_back();
  stack->push_back(t);
}

// StatementExpression -> ClassInstanceCreationExpression 
void parserASTStatementExpression_ClassInstanceCreationExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassInstanceCreationExpression);
  auto t = new TreeStatementExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTStatementExpressionVariants::ClassInstanceCreationExpression;
  t->classInstanceCreationExpression = dynamic_cast<TreeClassInstanceCreationExpression *>((*stack)[n - 1]);
  assert(t->classInstanceCreationExpression);
  stack->pop_back();
  stack->push_back(t);
}

// IfThenStatement -> if ( Expression ) Statement 
void parserASTIfThenStatement_IfLParExpressionRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TreeIfThenStatement;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTIfThenStatementVariants::IfLParExpressionRParStatement;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// IfThenElseStatement -> if ( Expression ) StatementNoShortIf else Statement 
void parserASTIfThenElseStatement_IfLParExpressionRParStatementNoShortIfElseStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::StatementNoShortIf);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TreeIfThenElseStatement;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTIfThenElseStatementVariants::IfLParExpressionRParStatementNoShortIfElseStatement;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 3]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 2]);
  assert(t->statementNoShortIf);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// IfThenElseStatementNoShortIf -> if ( Expression ) StatementNoShortIf else StatementNoShortIf 
void parserASTIfThenElseStatementNoShortIf_IfLParExpressionRParStatementNoShortIfElseStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::StatementNoShortIf);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeIfThenElseStatementNoShortIf;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTIfThenElseStatementNoShortIfVariants::IfLParExpressionRParStatementNoShortIfElseStatementNoShortIf;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 3]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 2]);
  assert(t->statementNoShortIf);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// WhileStatement -> while ( Expression ) Statement 
void parserASTWhileStatement_WhileLParExpressionRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TreeWhileStatement;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTWhileStatementVariants::WhileLParExpressionRParStatement;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// WhileStatementNoShortIf -> while ( Expression ) StatementNoShortIf 
void parserASTWhileStatementNoShortIf_WhileLParExpressionRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeWhileStatementNoShortIf;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTWhileStatementNoShortIfVariants::WhileLParExpressionRParStatementNoShortIf;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ; ; ) Statement 
void parserASTForStatement_ForLParSColSColRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTForStatementVariants::ForLParSColSColRParStatement;
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit ; ; ) Statement 
void parserASTForStatement_ForLParForInitSColSColRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTForStatementVariants::ForLParForInitSColSColRParStatement;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 2]);
  assert(t->forInit);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ; Expression ; ) Statement 
void parserASTForStatement_ForLParSColExpressionSColRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTForStatementVariants::ForLParSColExpressionSColRParStatement;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit ; Expression ; ) Statement 
void parserASTForStatement_ForLParForInitSColExpressionSColRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTForStatementVariants::ForLParForInitSColExpressionSColRParStatement;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 3]);
  assert(t->forInit);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ; ; ForUpdate ) Statement 
void parserASTForStatement_ForLParSColSColForUpdateRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTForStatementVariants::ForLParSColSColForUpdateRParStatement;
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit ; ; ForUpdate ) Statement 
void parserASTForStatement_ForLParForInitSColSColForUpdateRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTForStatementVariants::ForLParForInitSColSColForUpdateRParStatement;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 3]);
  assert(t->forInit);
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ; Expression ; ForUpdate ) Statement 
void parserASTForStatement_ForLParSColExpressionSColForUpdateRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTForStatementVariants::ForLParSColExpressionSColForUpdateRParStatement;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 3]);
  assert(t->expression);
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit ; Expression ; ForUpdate ) Statement 
void parserASTForStatement_ForLParForInitSColExpressionSColForUpdateRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 4);
  assert((*stack)[n - 4]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 3]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  parserASTSetTopParents(stack, 4, t);
  parserASTPopulateChildrenList(t, *stack, 4);
  t->variant = NTForStatementVariants::ForLParForInitSColExpressionSColForUpdateRParStatement;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 4]);
  assert(t->forInit);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 3]);
  assert(t->expression);
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ; ; ) StatementNoShortIf 
void parserASTForStatementNoShortIf_ForLParSColSColRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTForStatementNoShortIfVariants::ForLParSColSColRParStatementNoShortIf;
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit ; ; ) StatementNoShortIf 
void parserASTForStatementNoShortIf_ForLParForInitSColSColRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTForStatementNoShortIfVariants::ForLParForInitSColSColRParStatementNoShortIf;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 2]);
  assert(t->forInit);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ; Expression ; ) StatementNoShortIf 
void parserASTForStatementNoShortIf_ForLParSColExpressionSColRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTForStatementNoShortIfVariants::ForLParSColExpressionSColRParStatementNoShortIf;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit ; Expression ; ) StatementNoShortIf 
void parserASTForStatementNoShortIf_ForLParForInitSColExpressionSColRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTForStatementNoShortIfVariants::ForLParForInitSColExpressionSColRParStatementNoShortIf;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 3]);
  assert(t->forInit);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ; ; ForUpdate ) StatementNoShortIf 
void parserASTForStatementNoShortIf_ForLParSColSColForUpdateRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTForStatementNoShortIfVariants::ForLParSColSColForUpdateRParStatementNoShortIf;
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit ; ; ForUpdate ) StatementNoShortIf 
void parserASTForStatementNoShortIf_ForLParForInitSColSColForUpdateRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTForStatementNoShortIfVariants::ForLParForInitSColSColForUpdateRParStatementNoShortIf;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 3]);
  assert(t->forInit);
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ; Expression ; ForUpdate ) StatementNoShortIf 
void parserASTForStatementNoShortIf_ForLParSColExpressionSColForUpdateRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTForStatementNoShortIfVariants::ForLParSColExpressionSColForUpdateRParStatementNoShortIf;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 3]);
  assert(t->expression);
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit ; Expression ; ForUpdate ) StatementNoShortIf 
void parserASTForStatementNoShortIf_ForLParForInitSColExpressionSColForUpdateRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 4);
  assert((*stack)[n - 4]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 3]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  parserASTSetTopParents(stack, 4, t);
  parserASTPopulateChildrenList(t, *stack, 4);
  t->variant = NTForStatementNoShortIfVariants::ForLParForInitSColExpressionSColForUpdateRParStatementNoShortIf;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 4]);
  assert(t->forInit);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 3]);
  assert(t->expression);
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForInit -> StatementExpression 
void parserASTForInit_StatementExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementExpression);
  auto t = new TreeForInit;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTForInitVariants::StatementExpression;
  t->statementExpression = dynamic_cast<TreeStatementExpression *>((*stack)[n - 1]);
  assert(t->statementExpression);
  stack->pop_back();
  stack->push_back(t);
}

// ForInit -> LocalVariableDeclaration 
void parserASTForInit_LocalVariableDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::LocalVariableDeclaration);
  auto t = new TreeForInit;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTForInitVariants::LocalVariableDeclaration;
  t->localVariableDeclaration = dynamic_cast<TreeLocalVariableDeclaration *>((*stack)[n - 1]);
  assert(t->localVariableDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ForUpdate -> StatementExpression 
void parserASTForUpdate_StatementExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementExpression);
  auto t = new TreeForUpdate;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTForUpdateVariants::StatementExpression;
  t->statementExpression = dynamic_cast<TreeStatementExpression *>((*stack)[n - 1]);
  assert(t->statementExpression);
  stack->pop_back();
  stack->push_back(t);
}

// ReturnStatement -> return ; 
void parserASTReturnStatement_ReturnSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeReturnStatement;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTReturnStatementVariants::ReturnSCol;
  stack->push_back(t);
}

// ReturnStatement -> return Expression ; 
void parserASTReturnStatement_ReturnExpressionSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreeReturnStatement;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTReturnStatementVariants::ReturnExpressionSCol;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->push_back(t);
}

// Primary -> PrimaryNoNewArray 
void parserASTPrimary_PrimaryNoNewArray(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimaryNoNewArray);
  auto t = new TreePrimary;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTPrimaryVariants::PrimaryNoNewArray;
  t->primaryNoNewArray = dynamic_cast<TreePrimaryNoNewArray *>((*stack)[n - 1]);
  assert(t->primaryNoNewArray);
  stack->pop_back();
  stack->push_back(t);
}

// Primary -> ArrayCreationExpression 
void parserASTPrimary_ArrayCreationExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayCreationExpression);
  auto t = new TreePrimary;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTPrimaryVariants::ArrayCreationExpression;
  t->arrayCreationExpression = dynamic_cast<TreeArrayCreationExpression *>((*stack)[n - 1]);
  assert(t->arrayCreationExpression);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> Literal 
void parserASTPrimaryNoNewArray_Literal(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Literal);
  auto t = new TreePrimaryNoNewArray;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTPrimaryNoNewArrayVariants::Literal;
  t->literal = dynamic_cast<TreeLiteral *>((*stack)[n - 1]);
  assert(t->literal);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> This2 
void parserASTPrimaryNoNewArray_This2(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::This2);
  auto t = new TreePrimaryNoNewArray;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTPrimaryNoNewArrayVariants::This2;
  t->this2 = dynamic_cast<TreeThis2 *>((*stack)[n - 1]);
  assert(t->this2);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> ParenthesizedExpression 
void parserASTPrimaryNoNewArray_ParenthesizedExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ParenthesizedExpression);
  auto t = new TreePrimaryNoNewArray;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTPrimaryNoNewArrayVariants::ParenthesizedExpression;
  t->parenthesizedExpression = dynamic_cast<TreeParenthesizedExpression *>((*stack)[n - 1]);
  assert(t->parenthesizedExpression);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> ClassInstanceCreationExpression 
void parserASTPrimaryNoNewArray_ClassInstanceCreationExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassInstanceCreationExpression);
  auto t = new TreePrimaryNoNewArray;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTPrimaryNoNewArrayVariants::ClassInstanceCreationExpression;
  t->classInstanceCreationExpression = dynamic_cast<TreeClassInstanceCreationExpression *>((*stack)[n - 1]);
  assert(t->classInstanceCreationExpression);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> FieldAccess 
void parserASTPrimaryNoNewArray_FieldAccess(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FieldAccess);
  auto t = new TreePrimaryNoNewArray;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTPrimaryNoNewArrayVariants::FieldAccess;
  t->fieldAccess = dynamic_cast<TreeFieldAccess *>((*stack)[n - 1]);
  assert(t->fieldAccess);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> MethodInvocation 
void parserASTPrimaryNoNewArray_MethodInvocation(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodInvocation);
  auto t = new TreePrimaryNoNewArray;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTPrimaryNoNewArrayVariants::MethodInvocation;
  t->methodInvocation = dynamic_cast<TreeMethodInvocation *>((*stack)[n - 1]);
  assert(t->methodInvocation);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> ArrayAccess 
void parserASTPrimaryNoNewArray_ArrayAccess(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayAccess);
  auto t = new TreePrimaryNoNewArray;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTPrimaryNoNewArrayVariants::ArrayAccess;
  t->arrayAccess = dynamic_cast<TreeArrayAccess *>((*stack)[n - 1]);
  assert(t->arrayAccess);
  stack->pop_back();
  stack->push_back(t);
}

// This2 -> this 
void parserASTThis2_This2(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeThis2;
  parserASTSetTopParents(stack, 0, t);
  parserASTPopulateChildrenList(t, *stack, 0);
  t->variant = NTThis2Variants::This2;
  stack->push_back(t);
}

// ParenthesizedExpression -> ( Expression ) 
void parserASTParenthesizedExpression_LParExpressionRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreeParenthesizedExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTParenthesizedExpressionVariants::LParExpressionRPar;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->push_back(t);
}

// ClassInstanceCreationExpression -> new ClassType ( ) 
void parserASTClassInstanceCreationExpression_NewClassTypeLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassType);
  auto t = new TreeClassInstanceCreationExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTClassInstanceCreationExpressionVariants::NewClassTypeLParRPar;
  t->classType = dynamic_cast<TreeClassType *>((*stack)[n - 1]);
  assert(t->classType);
  stack->pop_back();
  stack->push_back(t);
}

// ClassInstanceCreationExpression -> new ClassType ( ArgumentList ) 
void parserASTClassInstanceCreationExpression_NewClassTypeLParArgumentListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassType);
  assert((*stack)[n - 1]->type == NonTerminalType::ArgumentList);
  auto t = new TreeClassInstanceCreationExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTClassInstanceCreationExpressionVariants::NewClassTypeLParArgumentListRPar;
  t->classType = dynamic_cast<TreeClassType *>((*stack)[n - 2]);
  assert(t->classType);
  t->argumentList = dynamic_cast<TreeArgumentList *>((*stack)[n - 1]);
  assert(t->argumentList);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArgumentList -> Expression 
void parserASTArgumentList_Expression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreeArgumentList;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTArgumentListVariants::Expression;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->push_back(t);
}

// ArgumentList -> ArgumentList , Expression 
void parserASTArgumentList_ArgumentListComExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ArgumentList);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreeArgumentList;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTArgumentListVariants::ArgumentListComExpression;
  t->argumentList = dynamic_cast<TreeArgumentList *>((*stack)[n - 2]);
  assert(t->argumentList);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayCreationExpression -> new PrimitiveType [ Expression ] 
void parserASTArrayCreationExpression_NewPrimitiveTypeLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PrimitiveType);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreeArrayCreationExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTArrayCreationExpressionVariants::NewPrimitiveTypeLSBrExpressionRSBr;
  t->primitiveType = dynamic_cast<TreePrimitiveType *>((*stack)[n - 2]);
  assert(t->primitiveType);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayCreationExpression -> new ClassOrInterfaceType [ Expression ] 
void parserASTArrayCreationExpression_NewClassOrInterfaceTypeLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassOrInterfaceType);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreeArrayCreationExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTArrayCreationExpressionVariants::NewClassOrInterfaceTypeLSBrExpressionRSBr;
  t->classOrInterfaceType = dynamic_cast<TreeClassOrInterfaceType *>((*stack)[n - 2]);
  assert(t->classOrInterfaceType);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// FieldAccess -> Primary . Identifier 
void parserASTFieldAccess_PrimaryDotIdentifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Primary);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TreeFieldAccess;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTFieldAccessVariants::PrimaryDotIdentifier;
  t->primary = dynamic_cast<TreePrimary *>((*stack)[n - 2]);
  assert(t->primary);
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Name ( ) 
void parserASTMethodInvocation_NameLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TreeMethodInvocation;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTMethodInvocationVariants::NameLParRPar;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Name ( ArgumentList ) 
void parserASTMethodInvocation_NameLParArgumentListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Name);
  assert((*stack)[n - 1]->type == NonTerminalType::ArgumentList);
  auto t = new TreeMethodInvocation;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTMethodInvocationVariants::NameLParArgumentListRPar;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 2]);
  assert(t->name);
  t->argumentList = dynamic_cast<TreeArgumentList *>((*stack)[n - 1]);
  assert(t->argumentList);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Primary . Identifier ( ) 
void parserASTMethodInvocation_PrimaryDotIdentifierLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Primary);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TreeMethodInvocation;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTMethodInvocationVariants::PrimaryDotIdentifierLParRPar;
  t->primary = dynamic_cast<TreePrimary *>((*stack)[n - 2]);
  assert(t->primary);
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Primary . Identifier ( ArgumentList ) 
void parserASTMethodInvocation_PrimaryDotIdentifierLParArgumentListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Primary);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::ArgumentList);
  auto t = new TreeMethodInvocation;
  parserASTSetTopParents(stack, 3, t);
  parserASTPopulateChildrenList(t, *stack, 3);
  t->variant = NTMethodInvocationVariants::PrimaryDotIdentifierLParArgumentListRPar;
  t->primary = dynamic_cast<TreePrimary *>((*stack)[n - 3]);
  assert(t->primary);
  t->identifier = dynamic_cast<TreeIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->argumentList = dynamic_cast<TreeArgumentList *>((*stack)[n - 1]);
  assert(t->argumentList);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayAccess -> Name [ Expression ] 
void parserASTArrayAccess_NameLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Name);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreeArrayAccess;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTArrayAccessVariants::NameLSBrExpressionRSBr;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 2]);
  assert(t->name);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayAccess -> PrimaryNoNewArray [ Expression ] 
void parserASTArrayAccess_PrimaryNoNewArrayLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PrimaryNoNewArray);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreeArrayAccess;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTArrayAccessVariants::PrimaryNoNewArrayLSBrExpressionRSBr;
  t->primaryNoNewArray = dynamic_cast<TreePrimaryNoNewArray *>((*stack)[n - 2]);
  assert(t->primaryNoNewArray);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpression -> - UnaryExpression 
void parserASTUnaryExpression_MinusUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeUnaryExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTUnaryExpressionVariants::MinusUnaryExpression;
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpression -> UnaryExpressionNotPlusMinus 
void parserASTUnaryExpression_UnaryExpressionNotPlusMinus(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpressionNotPlusMinus);
  auto t = new TreeUnaryExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTUnaryExpressionVariants::UnaryExpressionNotPlusMinus;
  t->unaryExpressionNotPlusMinus = dynamic_cast<TreeUnaryExpressionNotPlusMinus *>((*stack)[n - 1]);
  assert(t->unaryExpressionNotPlusMinus);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> Primary 
void parserASTUnaryExpressionNotPlusMinus_Primary(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Primary);
  auto t = new TreeUnaryExpressionNotPlusMinus;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTUnaryExpressionNotPlusMinusVariants::Primary;
  t->primary = dynamic_cast<TreePrimary *>((*stack)[n - 1]);
  assert(t->primary);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> Name 
void parserASTUnaryExpressionNotPlusMinus_Name(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TreeUnaryExpressionNotPlusMinus;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTUnaryExpressionNotPlusMinusVariants::Name;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> ~ UnaryExpression 
void parserASTUnaryExpressionNotPlusMinus_TilUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeUnaryExpressionNotPlusMinus;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTUnaryExpressionNotPlusMinusVariants::TilUnaryExpression;
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> ! UnaryExpression 
void parserASTUnaryExpressionNotPlusMinus_BangUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeUnaryExpressionNotPlusMinus;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTUnaryExpressionNotPlusMinusVariants::BangUnaryExpression;
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> CastExpression 
void parserASTUnaryExpressionNotPlusMinus_CastExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::CastExpression);
  auto t = new TreeUnaryExpressionNotPlusMinus;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTUnaryExpressionNotPlusMinusVariants::CastExpression;
  t->castExpression = dynamic_cast<TreeCastExpression *>((*stack)[n - 1]);
  assert(t->castExpression);
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( PrimitiveType ) UnaryExpression 
void parserASTCastExpression_LParPrimitiveTypeRParUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PrimitiveType);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeCastExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTCastExpressionVariants::LParPrimitiveTypeRParUnaryExpression;
  t->primitiveType = dynamic_cast<TreePrimitiveType *>((*stack)[n - 2]);
  assert(t->primitiveType);
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( PrimitiveType [ ] ) UnaryExpression 
void parserASTCastExpression_LParPrimitiveTypeLSBrRSBrRParUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PrimitiveType);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeCastExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTCastExpressionVariants::LParPrimitiveTypeLSBrRSBrRParUnaryExpression;
  t->primitiveType = dynamic_cast<TreePrimitiveType *>((*stack)[n - 2]);
  assert(t->primitiveType);
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( Expression ) UnaryExpressionNotPlusMinus 
void parserASTCastExpression_LParExpressionRParUnaryExpressionNotPlusMinus(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpressionNotPlusMinus);
  auto t = new TreeCastExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTCastExpressionVariants::LParExpressionRParUnaryExpressionNotPlusMinus;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->unaryExpressionNotPlusMinus = dynamic_cast<TreeUnaryExpressionNotPlusMinus *>((*stack)[n - 1]);
  assert(t->unaryExpressionNotPlusMinus);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( Name [ ] ) UnaryExpressionNotPlusMinus 
void parserASTCastExpression_LParNameLSBrRSBrRParUnaryExpressionNotPlusMinus(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Name);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpressionNotPlusMinus);
  auto t = new TreeCastExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTCastExpressionVariants::LParNameLSBrRSBrRParUnaryExpressionNotPlusMinus;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 2]);
  assert(t->name);
  t->unaryExpressionNotPlusMinus = dynamic_cast<TreeUnaryExpressionNotPlusMinus *>((*stack)[n - 1]);
  assert(t->unaryExpressionNotPlusMinus);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> UnaryExpression 
void parserASTMultiplicativeExpression_UnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeMultiplicativeExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTMultiplicativeExpressionVariants::UnaryExpression;
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> MultiplicativeExpression * UnaryExpression 
void parserASTMultiplicativeExpression_MultiplicativeExpressionStarUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::MultiplicativeExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeMultiplicativeExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTMultiplicativeExpressionVariants::MultiplicativeExpressionStarUnaryExpression;
  t->multiplicativeExpression = dynamic_cast<TreeMultiplicativeExpression *>((*stack)[n - 2]);
  assert(t->multiplicativeExpression);
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> MultiplicativeExpression / UnaryExpression 
void parserASTMultiplicativeExpression_MultiplicativeExpressionRSlashUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::MultiplicativeExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeMultiplicativeExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTMultiplicativeExpressionVariants::MultiplicativeExpressionRSlashUnaryExpression;
  t->multiplicativeExpression = dynamic_cast<TreeMultiplicativeExpression *>((*stack)[n - 2]);
  assert(t->multiplicativeExpression);
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> MultiplicativeExpression % UnaryExpression 
void parserASTMultiplicativeExpression_MultiplicativeExpressionPercUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::MultiplicativeExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeMultiplicativeExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTMultiplicativeExpressionVariants::MultiplicativeExpressionPercUnaryExpression;
  t->multiplicativeExpression = dynamic_cast<TreeMultiplicativeExpression *>((*stack)[n - 2]);
  assert(t->multiplicativeExpression);
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// AdditiveExpression -> MultiplicativeExpression 
void parserASTAdditiveExpression_MultiplicativeExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MultiplicativeExpression);
  auto t = new TreeAdditiveExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTAdditiveExpressionVariants::MultiplicativeExpression;
  t->multiplicativeExpression = dynamic_cast<TreeMultiplicativeExpression *>((*stack)[n - 1]);
  assert(t->multiplicativeExpression);
  stack->pop_back();
  stack->push_back(t);
}

// AdditiveExpression -> AdditiveExpression + MultiplicativeExpression 
void parserASTAdditiveExpression_AdditiveExpressionPlusMultiplicativeExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::AdditiveExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::MultiplicativeExpression);
  auto t = new TreeAdditiveExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTAdditiveExpressionVariants::AdditiveExpressionPlusMultiplicativeExpression;
  t->additiveExpression = dynamic_cast<TreeAdditiveExpression *>((*stack)[n - 2]);
  assert(t->additiveExpression);
  t->multiplicativeExpression = dynamic_cast<TreeMultiplicativeExpression *>((*stack)[n - 1]);
  assert(t->multiplicativeExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// AdditiveExpression -> AdditiveExpression - MultiplicativeExpression 
void parserASTAdditiveExpression_AdditiveExpressionMinusMultiplicativeExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::AdditiveExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::MultiplicativeExpression);
  auto t = new TreeAdditiveExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTAdditiveExpressionVariants::AdditiveExpressionMinusMultiplicativeExpression;
  t->additiveExpression = dynamic_cast<TreeAdditiveExpression *>((*stack)[n - 2]);
  assert(t->additiveExpression);
  t->multiplicativeExpression = dynamic_cast<TreeMultiplicativeExpression *>((*stack)[n - 1]);
  assert(t->multiplicativeExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> AdditiveExpression 
void parserASTRelationalExpression_AdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TreeRelationalExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTRelationalExpressionVariants::AdditiveExpression;
  t->additiveExpression = dynamic_cast<TreeAdditiveExpression *>((*stack)[n - 1]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression < AdditiveExpression 
void parserASTRelationalExpression_RelationalExpressionLeAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TreeRelationalExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTRelationalExpressionVariants::RelationalExpressionLeAdditiveExpression;
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 2]);
  assert(t->relationalExpression);
  t->additiveExpression = dynamic_cast<TreeAdditiveExpression *>((*stack)[n - 1]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression > AdditiveExpression 
void parserASTRelationalExpression_RelationalExpressionGrAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TreeRelationalExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTRelationalExpressionVariants::RelationalExpressionGrAdditiveExpression;
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 2]);
  assert(t->relationalExpression);
  t->additiveExpression = dynamic_cast<TreeAdditiveExpression *>((*stack)[n - 1]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression <= AdditiveExpression 
void parserASTRelationalExpression_RelationalExpressionLeEqAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TreeRelationalExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTRelationalExpressionVariants::RelationalExpressionLeEqAdditiveExpression;
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 2]);
  assert(t->relationalExpression);
  t->additiveExpression = dynamic_cast<TreeAdditiveExpression *>((*stack)[n - 1]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression >= AdditiveExpression 
void parserASTRelationalExpression_RelationalExpressionGrEqAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TreeRelationalExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTRelationalExpressionVariants::RelationalExpressionGrEqAdditiveExpression;
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 2]);
  assert(t->relationalExpression);
  t->additiveExpression = dynamic_cast<TreeAdditiveExpression *>((*stack)[n - 1]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression instanceof ReferenceType 
void parserASTRelationalExpression_RelationalExpressioninstanceofReferenceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::ReferenceType);
  auto t = new TreeRelationalExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTRelationalExpressionVariants::RelationalExpressioninstanceofReferenceType;
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 2]);
  assert(t->relationalExpression);
  t->referenceType = dynamic_cast<TreeReferenceType *>((*stack)[n - 1]);
  assert(t->referenceType);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// EqualityExpression -> RelationalExpression 
void parserASTEqualityExpression_RelationalExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  auto t = new TreeEqualityExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTEqualityExpressionVariants::RelationalExpression;
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 1]);
  assert(t->relationalExpression);
  stack->pop_back();
  stack->push_back(t);
}

// EqualityExpression -> EqualityExpression == RelationalExpression 
void parserASTEqualityExpression_EqualityExpressionEqEqRelationalExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::EqualityExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  auto t = new TreeEqualityExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTEqualityExpressionVariants::EqualityExpressionEqEqRelationalExpression;
  t->equalityExpression = dynamic_cast<TreeEqualityExpression *>((*stack)[n - 2]);
  assert(t->equalityExpression);
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 1]);
  assert(t->relationalExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// EqualityExpression -> EqualityExpression != RelationalExpression 
void parserASTEqualityExpression_EqualityExpressionBangEqRelationalExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::EqualityExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  auto t = new TreeEqualityExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTEqualityExpressionVariants::EqualityExpressionBangEqRelationalExpression;
  t->equalityExpression = dynamic_cast<TreeEqualityExpression *>((*stack)[n - 2]);
  assert(t->equalityExpression);
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 1]);
  assert(t->relationalExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ConditionalAndExpression -> EqualityExpression 
void parserASTConditionalAndExpression_EqualityExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::EqualityExpression);
  auto t = new TreeConditionalAndExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTConditionalAndExpressionVariants::EqualityExpression;
  t->equalityExpression = dynamic_cast<TreeEqualityExpression *>((*stack)[n - 1]);
  assert(t->equalityExpression);
  stack->pop_back();
  stack->push_back(t);
}

// ConditionalAndExpression -> ConditionalAndExpression && EqualityExpression 
void parserASTConditionalAndExpression_ConditionalAndExpressionAmpAmpEqualityExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ConditionalAndExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::EqualityExpression);
  auto t = new TreeConditionalAndExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTConditionalAndExpressionVariants::ConditionalAndExpressionAmpAmpEqualityExpression;
  t->conditionalAndExpression = dynamic_cast<TreeConditionalAndExpression *>((*stack)[n - 2]);
  assert(t->conditionalAndExpression);
  t->equalityExpression = dynamic_cast<TreeEqualityExpression *>((*stack)[n - 1]);
  assert(t->equalityExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ConditionalOrExpression -> ConditionalAndExpression 
void parserASTConditionalOrExpression_ConditionalAndExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ConditionalAndExpression);
  auto t = new TreeConditionalOrExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTConditionalOrExpressionVariants::ConditionalAndExpression;
  t->conditionalAndExpression = dynamic_cast<TreeConditionalAndExpression *>((*stack)[n - 1]);
  assert(t->conditionalAndExpression);
  stack->pop_back();
  stack->push_back(t);
}

// ConditionalOrExpression -> ConditionalOrExpression || ConditionalAndExpression 
void parserASTConditionalOrExpression_ConditionalOrExpressionOrOrConditionalAndExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ConditionalOrExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::ConditionalAndExpression);
  auto t = new TreeConditionalOrExpression;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTConditionalOrExpressionVariants::ConditionalOrExpressionOrOrConditionalAndExpression;
  t->conditionalOrExpression = dynamic_cast<TreeConditionalOrExpression *>((*stack)[n - 2]);
  assert(t->conditionalOrExpression);
  t->conditionalAndExpression = dynamic_cast<TreeConditionalAndExpression *>((*stack)[n - 1]);
  assert(t->conditionalAndExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// AssignmentExpression -> ConditionalOrExpression 
void parserASTAssignmentExpression_ConditionalOrExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ConditionalOrExpression);
  auto t = new TreeAssignmentExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTAssignmentExpressionVariants::ConditionalOrExpression;
  t->conditionalOrExpression = dynamic_cast<TreeConditionalOrExpression *>((*stack)[n - 1]);
  assert(t->conditionalOrExpression);
  stack->pop_back();
  stack->push_back(t);
}

// AssignmentExpression -> Assignment 
void parserASTAssignmentExpression_Assignment(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Assignment);
  auto t = new TreeAssignmentExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTAssignmentExpressionVariants::Assignment;
  t->assignment = dynamic_cast<TreeAssignment *>((*stack)[n - 1]);
  assert(t->assignment);
  stack->pop_back();
  stack->push_back(t);
}

// Assignment -> LeftHandSide = AssignmentExpression 
void parserASTAssignment_LeftHandSideEqAssignmentExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::LeftHandSide);
  assert((*stack)[n - 1]->type == NonTerminalType::AssignmentExpression);
  auto t = new TreeAssignment;
  parserASTSetTopParents(stack, 2, t);
  parserASTPopulateChildrenList(t, *stack, 2);
  t->variant = NTAssignmentVariants::LeftHandSideEqAssignmentExpression;
  t->leftHandSide = dynamic_cast<TreeLeftHandSide *>((*stack)[n - 2]);
  assert(t->leftHandSide);
  t->assignmentExpression = dynamic_cast<TreeAssignmentExpression *>((*stack)[n - 1]);
  assert(t->assignmentExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// LeftHandSide -> Name 
void parserASTLeftHandSide_Name(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TreeLeftHandSide;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTLeftHandSideVariants::Name;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// LeftHandSide -> FieldAccess 
void parserASTLeftHandSide_FieldAccess(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FieldAccess);
  auto t = new TreeLeftHandSide;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTLeftHandSideVariants::FieldAccess;
  t->fieldAccess = dynamic_cast<TreeFieldAccess *>((*stack)[n - 1]);
  assert(t->fieldAccess);
  stack->pop_back();
  stack->push_back(t);
}

// LeftHandSide -> ArrayAccess 
void parserASTLeftHandSide_ArrayAccess(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayAccess);
  auto t = new TreeLeftHandSide;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTLeftHandSideVariants::ArrayAccess;
  t->arrayAccess = dynamic_cast<TreeArrayAccess *>((*stack)[n - 1]);
  assert(t->arrayAccess);
  stack->pop_back();
  stack->push_back(t);
}

// Expression -> AssignmentExpression 
void parserASTExpression_AssignmentExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AssignmentExpression);
  auto t = new TreeExpression;
  parserASTSetTopParents(stack, 1, t);
  parserASTPopulateChildrenList(t, *stack, 1);
  t->variant = NTExpressionVariants::AssignmentExpression;
  t->assignmentExpression = dynamic_cast<TreeAssignmentExpression *>((*stack)[n - 1]);
  assert(t->assignmentExpression);
  stack->pop_back();
  stack->push_back(t);
}

void parserASTDispatcher(vector<Tree *> *stack, int ruleID) {
  static const parserASTFunc table[] = {
    parserASTGoal_BOFCompilationUnitEof, 
    parserASTLiteral_IntegerLiteral, 
    parserASTLiteral_BooleanLiteral, 
    parserASTLiteral_CharacterLiteral, 
    parserASTLiteral_StringLiteral, 
    parserASTLiteral_NullLiteral, 
    parserASTType_PrimitiveType, 
    parserASTType_ReferenceType, 
    parserASTPrimitiveType_boolean, 
    parserASTPrimitiveType_byte, 
    parserASTPrimitiveType_Short, 
    parserASTPrimitiveType_Int, 
    parserASTPrimitiveType_Char, 
    parserASTReferenceType_ClassOrInterfaceType, 
    parserASTReferenceType_ArrayType, 
    parserASTClassOrInterfaceType_Name, 
    parserASTClassType_ClassOrInterfaceType, 
    parserASTInterfaceType_ClassOrInterfaceType, 
    parserASTArrayType_PrimitiveTypeLSBrRSBr, 
    parserASTArrayType_NameLSBrRSBr, 
    parserASTName_Identifier, 
    parserASTName_NameDotIdentifier, 
    parserASTCompilationUnit_, 
    parserASTCompilationUnit_PackageDeclaration, 
    parserASTCompilationUnit_ImportDeclarations, 
    parserASTCompilationUnit_PackageDeclarationImportDeclarations, 
    parserASTCompilationUnit_TypeDeclaration, 
    parserASTCompilationUnit_PackageDeclarationTypeDeclaration, 
    parserASTCompilationUnit_ImportDeclarationsTypeDeclaration, 
    parserASTCompilationUnit_PackageDeclarationImportDeclarationsTypeDeclaration, 
    parserASTImportDeclarations_ImportDeclaration, 
    parserASTImportDeclarations_ImportDeclarationsImportDeclaration, 
    parserASTPackageDeclaration_packageNameSCol, 
    parserASTImportDeclaration_SingleTypeImportDeclaration, 
    parserASTImportDeclaration_TypeImportOnDemandDeclaration, 
    parserASTSingleTypeImportDeclaration_importNameSCol, 
    parserASTTypeImportOnDemandDeclaration_importNameDotStarSCol, 
    parserASTTypeDeclaration_ClassDeclaration, 
    parserASTTypeDeclaration_InterfaceDeclaration, 
    parserASTTypeDeclaration_SCol, 
    parserASTModifiers_Modifier, 
    parserASTModifiers_ModifiersModifier, 
    parserASTModifier_Public, 
    parserASTModifier_Protected, 
    parserASTModifier_Static, 
    parserASTModifier_abstract, 
    parserASTModifier_final, 
    parserASTModifier_native, 
    parserASTClassDeclaration_ClassIdentifierClassBody, 
    parserASTClassDeclaration_ModifiersClassIdentifierClassBody, 
    parserASTClassDeclaration_ClassIdentifierextendsClassTypeClassBody, 
    parserASTClassDeclaration_ModifiersClassIdentifierextendsClassTypeClassBody, 
    parserASTClassDeclaration_ClassIdentifierimplementsInterfaceTypeListClassBody, 
    parserASTClassDeclaration_ModifiersClassIdentifierimplementsInterfaceTypeListClassBody, 
    parserASTClassDeclaration_ClassIdentifierextendsClassTypeimplementsInterfaceTypeListClassBody, 
    parserASTClassDeclaration_ModifiersClassIdentifierextendsClassTypeimplementsInterfaceTypeListClassBody, 
    parserASTInterfaceTypeList_InterfaceType, 
    parserASTInterfaceTypeList_InterfaceTypeListComInterfaceType, 
    parserASTClassBody_LCBrRCBr, 
    parserASTClassBody_LCBrClassMemberDeclarationsRCBr, 
    parserASTClassMemberDeclarations_ClassMemberDeclaration, 
    parserASTClassMemberDeclarations_ClassMemberDeclarationsClassMemberDeclaration, 
    parserASTClassMemberDeclaration_FieldDeclaration, 
    parserASTClassMemberDeclaration_MethodDeclaration, 
    parserASTClassMemberDeclaration_ConstructorDeclaration, 
    parserASTFieldDeclaration_TypeVariableDeclaratorSCol, 
    parserASTFieldDeclaration_ModifiersTypeVariableDeclaratorSCol, 
    parserASTVariableDeclarator_Identifier, 
    parserASTVariableDeclarator_IdentifierEqExpression, 
    parserASTMethodDeclaration_MethodHeaderMethodBody, 
    parserASTMethodHeader_TypeMethodDeclarator, 
    parserASTMethodHeader_ModifiersTypeMethodDeclarator, 
    parserASTMethodHeader_VoidMethodDeclarator, 
    parserASTMethodHeader_ModifiersVoidMethodDeclarator, 
    parserASTMethodDeclarator_IdentifierLParRPar, 
    parserASTMethodDeclarator_IdentifierLParFormalParameterListRPar, 
    parserASTFormalParameterList_FormalParameter, 
    parserASTFormalParameterList_FormalParameterListComFormalParameter, 
    parserASTFormalParameter_TypeIdentifier, 
    parserASTMethodBody_Block, 
    parserASTMethodBody_AbstractMethodBody, 
    parserASTAbstractMethodBody_SCol, 
    parserASTConstructorDeclaration_ConstructorDeclaratorBlock, 
    parserASTConstructorDeclaration_ModifiersConstructorDeclaratorBlock, 
    parserASTConstructorDeclarator_IdentifierLParRPar, 
    parserASTConstructorDeclarator_IdentifierLParFormalParameterListRPar, 
    parserASTInterfaceDeclaration_interfaceIdentifierInterfaceBody, 
    parserASTInterfaceDeclaration_ModifiersinterfaceIdentifierInterfaceBody, 
    parserASTInterfaceDeclaration_interfaceIdentifierExtendsInterfacesInterfaceBody, 
    parserASTInterfaceDeclaration_ModifiersinterfaceIdentifierExtendsInterfacesInterfaceBody, 
    parserASTExtendsInterfaces_extendsInterfaceType, 
    parserASTExtendsInterfaces_ExtendsInterfacesComInterfaceType, 
    parserASTInterfaceBody_LCBrRCBr, 
    parserASTInterfaceBody_LCBrInterfaceMemberDeclarationsRCBr, 
    parserASTInterfaceMemberDeclarations_InterfaceMemberDeclaration, 
    parserASTInterfaceMemberDeclarations_InterfaceMemberDeclarationsInterfaceMemberDeclaration, 
    parserASTInterfaceMemberDeclaration_AbstractMethodDeclaration, 
    parserASTAbstractMethodDeclaration_MethodHeaderSCol, 
    parserASTBlock_LCBrRCBr, 
    parserASTBlock_LCBrBlockStatementsRCBr, 
    parserASTBlockStatements_BlockStatement, 
    parserASTBlockStatements_BlockStatementsBlockStatement, 
    parserASTBlockStatement_LocalVariableDeclarationStatement, 
    parserASTBlockStatement_Statement, 
    parserASTLocalVariableDeclarationStatement_LocalVariableDeclarationSCol, 
    parserASTLocalVariableDeclaration_TypeVariableDeclarator, 
    parserASTStatement_StatementWithoutTrailingSubstatement, 
    parserASTStatement_IfThenStatement, 
    parserASTStatement_IfThenElseStatement, 
    parserASTStatement_WhileStatement, 
    parserASTStatement_ForStatement, 
    parserASTStatementNoShortIf_StatementWithoutTrailingSubstatement, 
    parserASTStatementNoShortIf_IfThenElseStatementNoShortIf, 
    parserASTStatementNoShortIf_WhileStatementNoShortIf, 
    parserASTStatementNoShortIf_ForStatementNoShortIf, 
    parserASTStatementWithoutTrailingSubstatement_Block, 
    parserASTStatementWithoutTrailingSubstatement_EmptyStatement, 
    parserASTStatementWithoutTrailingSubstatement_ExpressionStatement, 
    parserASTStatementWithoutTrailingSubstatement_ReturnStatement, 
    parserASTEmptyStatement_SCol, 
    parserASTExpressionStatement_StatementExpressionSCol, 
    parserASTStatementExpression_Assignment, 
    parserASTStatementExpression_MethodInvocation, 
    parserASTStatementExpression_ClassInstanceCreationExpression, 
    parserASTIfThenStatement_IfLParExpressionRParStatement, 
    parserASTIfThenElseStatement_IfLParExpressionRParStatementNoShortIfElseStatement, 
    parserASTIfThenElseStatementNoShortIf_IfLParExpressionRParStatementNoShortIfElseStatementNoShortIf, 
    parserASTWhileStatement_WhileLParExpressionRParStatement, 
    parserASTWhileStatementNoShortIf_WhileLParExpressionRParStatementNoShortIf, 
    parserASTForStatement_ForLParSColSColRParStatement, 
    parserASTForStatement_ForLParForInitSColSColRParStatement, 
    parserASTForStatement_ForLParSColExpressionSColRParStatement, 
    parserASTForStatement_ForLParForInitSColExpressionSColRParStatement, 
    parserASTForStatement_ForLParSColSColForUpdateRParStatement, 
    parserASTForStatement_ForLParForInitSColSColForUpdateRParStatement, 
    parserASTForStatement_ForLParSColExpressionSColForUpdateRParStatement, 
    parserASTForStatement_ForLParForInitSColExpressionSColForUpdateRParStatement, 
    parserASTForStatementNoShortIf_ForLParSColSColRParStatementNoShortIf, 
    parserASTForStatementNoShortIf_ForLParForInitSColSColRParStatementNoShortIf, 
    parserASTForStatementNoShortIf_ForLParSColExpressionSColRParStatementNoShortIf, 
    parserASTForStatementNoShortIf_ForLParForInitSColExpressionSColRParStatementNoShortIf, 
    parserASTForStatementNoShortIf_ForLParSColSColForUpdateRParStatementNoShortIf, 
    parserASTForStatementNoShortIf_ForLParForInitSColSColForUpdateRParStatementNoShortIf, 
    parserASTForStatementNoShortIf_ForLParSColExpressionSColForUpdateRParStatementNoShortIf, 
    parserASTForStatementNoShortIf_ForLParForInitSColExpressionSColForUpdateRParStatementNoShortIf, 
    parserASTForInit_StatementExpression, 
    parserASTForInit_LocalVariableDeclaration, 
    parserASTForUpdate_StatementExpression, 
    parserASTReturnStatement_ReturnSCol, 
    parserASTReturnStatement_ReturnExpressionSCol, 
    parserASTPrimary_PrimaryNoNewArray, 
    parserASTPrimary_ArrayCreationExpression, 
    parserASTPrimaryNoNewArray_Literal, 
    parserASTPrimaryNoNewArray_This2, 
    parserASTPrimaryNoNewArray_ParenthesizedExpression, 
    parserASTPrimaryNoNewArray_ClassInstanceCreationExpression, 
    parserASTPrimaryNoNewArray_FieldAccess, 
    parserASTPrimaryNoNewArray_MethodInvocation, 
    parserASTPrimaryNoNewArray_ArrayAccess, 
    parserASTThis2_This2, 
    parserASTParenthesizedExpression_LParExpressionRPar, 
    parserASTClassInstanceCreationExpression_NewClassTypeLParRPar, 
    parserASTClassInstanceCreationExpression_NewClassTypeLParArgumentListRPar, 
    parserASTArgumentList_Expression, 
    parserASTArgumentList_ArgumentListComExpression, 
    parserASTArrayCreationExpression_NewPrimitiveTypeLSBrExpressionRSBr, 
    parserASTArrayCreationExpression_NewClassOrInterfaceTypeLSBrExpressionRSBr, 
    parserASTFieldAccess_PrimaryDotIdentifier, 
    parserASTMethodInvocation_NameLParRPar, 
    parserASTMethodInvocation_NameLParArgumentListRPar, 
    parserASTMethodInvocation_PrimaryDotIdentifierLParRPar, 
    parserASTMethodInvocation_PrimaryDotIdentifierLParArgumentListRPar, 
    parserASTArrayAccess_NameLSBrExpressionRSBr, 
    parserASTArrayAccess_PrimaryNoNewArrayLSBrExpressionRSBr, 
    parserASTUnaryExpression_MinusUnaryExpression, 
    parserASTUnaryExpression_UnaryExpressionNotPlusMinus, 
    parserASTUnaryExpressionNotPlusMinus_Primary, 
    parserASTUnaryExpressionNotPlusMinus_Name, 
    parserASTUnaryExpressionNotPlusMinus_TilUnaryExpression, 
    parserASTUnaryExpressionNotPlusMinus_BangUnaryExpression, 
    parserASTUnaryExpressionNotPlusMinus_CastExpression, 
    parserASTCastExpression_LParPrimitiveTypeRParUnaryExpression, 
    parserASTCastExpression_LParPrimitiveTypeLSBrRSBrRParUnaryExpression, 
    parserASTCastExpression_LParExpressionRParUnaryExpressionNotPlusMinus, 
    parserASTCastExpression_LParNameLSBrRSBrRParUnaryExpressionNotPlusMinus, 
    parserASTMultiplicativeExpression_UnaryExpression, 
    parserASTMultiplicativeExpression_MultiplicativeExpressionStarUnaryExpression, 
    parserASTMultiplicativeExpression_MultiplicativeExpressionRSlashUnaryExpression, 
    parserASTMultiplicativeExpression_MultiplicativeExpressionPercUnaryExpression, 
    parserASTAdditiveExpression_MultiplicativeExpression, 
    parserASTAdditiveExpression_AdditiveExpressionPlusMultiplicativeExpression, 
    parserASTAdditiveExpression_AdditiveExpressionMinusMultiplicativeExpression, 
    parserASTRelationalExpression_AdditiveExpression, 
    parserASTRelationalExpression_RelationalExpressionLeAdditiveExpression, 
    parserASTRelationalExpression_RelationalExpressionGrAdditiveExpression, 
    parserASTRelationalExpression_RelationalExpressionLeEqAdditiveExpression, 
    parserASTRelationalExpression_RelationalExpressionGrEqAdditiveExpression, 
    parserASTRelationalExpression_RelationalExpressioninstanceofReferenceType, 
    parserASTEqualityExpression_RelationalExpression, 
    parserASTEqualityExpression_EqualityExpressionEqEqRelationalExpression, 
    parserASTEqualityExpression_EqualityExpressionBangEqRelationalExpression, 
    parserASTConditionalAndExpression_EqualityExpression, 
    parserASTConditionalAndExpression_ConditionalAndExpressionAmpAmpEqualityExpression, 
    parserASTConditionalOrExpression_ConditionalAndExpression, 
    parserASTConditionalOrExpression_ConditionalOrExpressionOrOrConditionalAndExpression, 
    parserASTAssignmentExpression_ConditionalOrExpression, 
    parserASTAssignmentExpression_Assignment, 
    parserASTAssignment_LeftHandSideEqAssignmentExpression, 
    parserASTLeftHandSide_Name, 
    parserASTLeftHandSide_FieldAccess, 
    parserASTLeftHandSide_ArrayAccess, 
    parserASTExpression_AssignmentExpression, 
  };
  table[ruleID](stack);
}

} // namespace Parse 
#endif // PARSERAST_DISABLED
