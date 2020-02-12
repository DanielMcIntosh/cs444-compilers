#include "parseTreeBase.h"
#include "parseTree.h"
#include "parseTreeNode.h"

namespace Parse { 

using namespace std;

// Goal -> BOF CompilationUnit EOF 
void ptGoal_BOFCompilationUnitEof(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::CompilationUnit);
  auto t = new TGoal;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TGoalV::BOFCompilationUnitEof;
  t->oneNt = false;
  t->compilationUnit = dynamic_cast<TCompilationUnit *>((*stack)[n - 1]);
  assert(t->compilationUnit);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> IntegerLiteral 
void ptLiteral_IntegerLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::IntegerLiteral);
  auto t = new TLiteral;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLiteralV::IntegerLiteral;
  t->oneNt = false;
  t->integerLiteral = dynamic_cast<TIntegerLiteral *>((*stack)[n - 1]);
  assert(t->integerLiteral);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> BooleanLiteral 
void ptLiteral_BooleanLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::BooleanLiteral);
  auto t = new TLiteral;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLiteralV::BooleanLiteral;
  t->oneNt = false;
  t->booleanLiteral = dynamic_cast<TBooleanLiteral *>((*stack)[n - 1]);
  assert(t->booleanLiteral);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> CharacterLiteral 
void ptLiteral_CharacterLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::CharacterLiteral);
  auto t = new TLiteral;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLiteralV::CharacterLiteral;
  t->oneNt = false;
  t->characterLiteral = dynamic_cast<TCharacterLiteral *>((*stack)[n - 1]);
  assert(t->characterLiteral);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> StringLiteral 
void ptLiteral_StringLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StringLiteral);
  auto t = new TLiteral;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLiteralV::StringLiteral;
  t->oneNt = false;
  t->stringLiteral = dynamic_cast<TStringLiteral *>((*stack)[n - 1]);
  assert(t->stringLiteral);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> NullLiteral 
void ptLiteral_NullLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::NullLiteral);
  auto t = new TLiteral;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLiteralV::NullLiteral;
  t->oneNt = false;
  t->nullLiteral = dynamic_cast<TNullLiteral *>((*stack)[n - 1]);
  assert(t->nullLiteral);
  stack->pop_back();
  stack->push_back(t);
}

// Type -> PrimitiveType 
void ptType_PrimitiveType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimitiveType);
  auto t = new TType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TTypeV::PrimitiveType;
  t->oneNt = true;
  t->primitiveType = dynamic_cast<TPrimitiveType *>((*stack)[n - 1]);
  assert(t->primitiveType);
  stack->pop_back();
  stack->push_back(t);
}

// Type -> ReferenceType 
void ptType_ReferenceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ReferenceType);
  auto t = new TType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TTypeV::ReferenceType;
  t->oneNt = true;
  t->referenceType = dynamic_cast<TReferenceType *>((*stack)[n - 1]);
  assert(t->referenceType);
  stack->pop_back();
  stack->push_back(t);
}

// PrimitiveType -> boolean 
void ptPrimitiveType_boolean(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TPrimitiveType;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TPrimitiveTypeV::boolean;
  t->oneNt = false;
  stack->push_back(t);
}

// PrimitiveType -> byte 
void ptPrimitiveType_byte(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TPrimitiveType;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TPrimitiveTypeV::byte;
  t->oneNt = false;
  stack->push_back(t);
}

// PrimitiveType -> short 
void ptPrimitiveType_Short(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TPrimitiveType;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TPrimitiveTypeV::Short;
  t->oneNt = false;
  stack->push_back(t);
}

// PrimitiveType -> int 
void ptPrimitiveType_Int(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TPrimitiveType;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TPrimitiveTypeV::Int;
  t->oneNt = false;
  stack->push_back(t);
}

// PrimitiveType -> char 
void ptPrimitiveType_Char(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TPrimitiveType;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TPrimitiveTypeV::Char;
  t->oneNt = false;
  stack->push_back(t);
}

// ReferenceType -> ClassOrInterfaceType 
void ptReferenceType_ClassOrInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassOrInterfaceType);
  auto t = new TReferenceType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TReferenceTypeV::ClassOrInterfaceType;
  t->oneNt = true;
  t->classOrInterfaceType = dynamic_cast<TClassOrInterfaceType *>((*stack)[n - 1]);
  assert(t->classOrInterfaceType);
  stack->pop_back();
  stack->push_back(t);
}

// ReferenceType -> ArrayType 
void ptReferenceType_ArrayType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayType);
  auto t = new TReferenceType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TReferenceTypeV::ArrayType;
  t->oneNt = true;
  t->arrayType = dynamic_cast<TArrayType *>((*stack)[n - 1]);
  assert(t->arrayType);
  stack->pop_back();
  stack->push_back(t);
}

// ClassOrInterfaceType -> Name 
void ptClassOrInterfaceType_Name(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TClassOrInterfaceType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassOrInterfaceTypeV::Name;
  t->oneNt = true;
  t->name = dynamic_cast<TName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// ClassType -> ClassOrInterfaceType 
void ptClassType_ClassOrInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassOrInterfaceType);
  auto t = new TClassType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassTypeV::ClassOrInterfaceType;
  t->oneNt = true;
  t->classOrInterfaceType = dynamic_cast<TClassOrInterfaceType *>((*stack)[n - 1]);
  assert(t->classOrInterfaceType);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceType -> ClassOrInterfaceType 
void ptInterfaceType_ClassOrInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassOrInterfaceType);
  auto t = new TInterfaceType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TInterfaceTypeV::ClassOrInterfaceType;
  t->oneNt = true;
  t->classOrInterfaceType = dynamic_cast<TClassOrInterfaceType *>((*stack)[n - 1]);
  assert(t->classOrInterfaceType);
  stack->pop_back();
  stack->push_back(t);
}

// ArrayType -> PrimitiveType [ ] 
void ptArrayType_PrimitiveTypeLSBrRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimitiveType);
  auto t = new TArrayType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TArrayTypeV::PrimitiveTypeLSBrRSBr;
  t->oneNt = false;
  t->primitiveType = dynamic_cast<TPrimitiveType *>((*stack)[n - 1]);
  assert(t->primitiveType);
  stack->pop_back();
  stack->push_back(t);
}

// ArrayType -> Name [ ] 
void ptArrayType_NameLSBrRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TArrayType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TArrayTypeV::NameLSBrRSBr;
  t->oneNt = false;
  t->name = dynamic_cast<TName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// Name -> Identifier 
void ptName_Identifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TName;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TNameV::Identifier;
  t->oneNt = false;
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->push_back(t);
}

// Name -> Name . Identifier 
void ptName_NameDotIdentifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Name);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TName;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TNameV::NameDotIdentifier;
  t->oneNt = false;
  t->name = dynamic_cast<TName *>((*stack)[n - 2]);
  assert(t->name);
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> 
void ptCompilationUnit_(vector<Tree *> *stack) {
}

// CompilationUnit -> PackageDeclaration 
void ptCompilationUnit_PackageDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PackageDeclaration);
  auto t = new TCompilationUnit;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TCompilationUnitV::PackageDeclaration;
  t->oneNt = true;
  t->packageDeclaration = dynamic_cast<TPackageDeclaration *>((*stack)[n - 1]);
  assert(t->packageDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> ImportDeclarations 
void ptCompilationUnit_ImportDeclarations(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclarations);
  auto t = new TCompilationUnit;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TCompilationUnitV::ImportDeclarations;
  t->oneNt = true;
  t->importDeclarations = dynamic_cast<TImportDeclarations *>((*stack)[n - 1]);
  assert(t->importDeclarations);
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> PackageDeclaration ImportDeclarations 
void ptCompilationUnit_PackageDeclarationImportDeclarations(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PackageDeclaration);
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclarations);
  auto t = new TCompilationUnit;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCompilationUnitV::PackageDeclarationImportDeclarations;
  t->oneNt = false;
  t->packageDeclaration = dynamic_cast<TPackageDeclaration *>((*stack)[n - 2]);
  assert(t->packageDeclaration);
  t->importDeclarations = dynamic_cast<TImportDeclarations *>((*stack)[n - 1]);
  assert(t->importDeclarations);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> TypeDeclaration 
void ptCompilationUnit_TypeDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclaration);
  auto t = new TCompilationUnit;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TCompilationUnitV::TypeDeclaration;
  t->oneNt = true;
  t->typeDeclaration = dynamic_cast<TTypeDeclaration *>((*stack)[n - 1]);
  assert(t->typeDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> PackageDeclaration TypeDeclaration 
void ptCompilationUnit_PackageDeclarationTypeDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PackageDeclaration);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclaration);
  auto t = new TCompilationUnit;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCompilationUnitV::PackageDeclarationTypeDeclaration;
  t->oneNt = false;
  t->packageDeclaration = dynamic_cast<TPackageDeclaration *>((*stack)[n - 2]);
  assert(t->packageDeclaration);
  t->typeDeclaration = dynamic_cast<TTypeDeclaration *>((*stack)[n - 1]);
  assert(t->typeDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> ImportDeclarations TypeDeclaration 
void ptCompilationUnit_ImportDeclarationsTypeDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ImportDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclaration);
  auto t = new TCompilationUnit;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCompilationUnitV::ImportDeclarationsTypeDeclaration;
  t->oneNt = false;
  t->importDeclarations = dynamic_cast<TImportDeclarations *>((*stack)[n - 2]);
  assert(t->importDeclarations);
  t->typeDeclaration = dynamic_cast<TTypeDeclaration *>((*stack)[n - 1]);
  assert(t->typeDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> PackageDeclaration ImportDeclarations TypeDeclaration 
void ptCompilationUnit_PackageDeclarationImportDeclarationsTypeDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::PackageDeclaration);
  assert((*stack)[n - 2]->type == NonTerminalType::ImportDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclaration);
  auto t = new TCompilationUnit;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TCompilationUnitV::PackageDeclarationImportDeclarationsTypeDeclaration;
  t->oneNt = false;
  t->packageDeclaration = dynamic_cast<TPackageDeclaration *>((*stack)[n - 3]);
  assert(t->packageDeclaration);
  t->importDeclarations = dynamic_cast<TImportDeclarations *>((*stack)[n - 2]);
  assert(t->importDeclarations);
  t->typeDeclaration = dynamic_cast<TTypeDeclaration *>((*stack)[n - 1]);
  assert(t->typeDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ImportDeclarations -> ImportDeclaration 
void ptImportDeclarations_ImportDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclaration);
  auto t = new TImportDeclarations;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TImportDeclarationsV::ImportDeclaration;
  t->oneNt = true;
  t->importDeclaration = dynamic_cast<TImportDeclaration *>((*stack)[n - 1]);
  assert(t->importDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ImportDeclarations -> ImportDeclarations ImportDeclaration 
void ptImportDeclarations_ImportDeclarationsImportDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ImportDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclaration);
  auto t = new TImportDeclarations;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TImportDeclarationsV::ImportDeclarationsImportDeclaration;
  t->oneNt = false;
  t->importDeclarations = dynamic_cast<TImportDeclarations *>((*stack)[n - 2]);
  assert(t->importDeclarations);
  t->importDeclaration = dynamic_cast<TImportDeclaration *>((*stack)[n - 1]);
  assert(t->importDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// PackageDeclaration -> package Name ; 
void ptPackageDeclaration_packageNameSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TPackageDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPackageDeclarationV::packageNameSCol;
  t->oneNt = false;
  t->name = dynamic_cast<TName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// ImportDeclaration -> SingleTypeImportDeclaration 
void ptImportDeclaration_SingleTypeImportDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::SingleTypeImportDeclaration);
  auto t = new TImportDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TImportDeclarationV::SingleTypeImportDeclaration;
  t->oneNt = true;
  t->singleTypeImportDeclaration = dynamic_cast<TSingleTypeImportDeclaration *>((*stack)[n - 1]);
  assert(t->singleTypeImportDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ImportDeclaration -> TypeImportOnDemandDeclaration 
void ptImportDeclaration_TypeImportOnDemandDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeImportOnDemandDeclaration);
  auto t = new TImportDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TImportDeclarationV::TypeImportOnDemandDeclaration;
  t->oneNt = true;
  t->typeImportOnDemandDeclaration = dynamic_cast<TTypeImportOnDemandDeclaration *>((*stack)[n - 1]);
  assert(t->typeImportOnDemandDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// SingleTypeImportDeclaration -> import Name ; 
void ptSingleTypeImportDeclaration_importNameSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TSingleTypeImportDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TSingleTypeImportDeclarationV::importNameSCol;
  t->oneNt = false;
  t->name = dynamic_cast<TName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// TypeImportOnDemandDeclaration -> import Name . * ; 
void ptTypeImportOnDemandDeclaration_importNameDotStarSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TTypeImportOnDemandDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TTypeImportOnDemandDeclarationV::importNameDotStarSCol;
  t->oneNt = false;
  t->name = dynamic_cast<TName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// TypeDeclaration -> ClassDeclaration 
void ptTypeDeclaration_ClassDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassDeclaration);
  auto t = new TTypeDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TTypeDeclarationV::ClassDeclaration;
  t->oneNt = true;
  t->classDeclaration = dynamic_cast<TClassDeclaration *>((*stack)[n - 1]);
  assert(t->classDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// TypeDeclaration -> InterfaceDeclaration 
void ptTypeDeclaration_InterfaceDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceDeclaration);
  auto t = new TTypeDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TTypeDeclarationV::InterfaceDeclaration;
  t->oneNt = true;
  t->interfaceDeclaration = dynamic_cast<TInterfaceDeclaration *>((*stack)[n - 1]);
  assert(t->interfaceDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// TypeDeclaration -> ; 
void ptTypeDeclaration_SCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TTypeDeclaration;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TTypeDeclarationV::SCol;
  t->oneNt = false;
  stack->push_back(t);
}

// Modifiers -> Modifier 
void ptModifiers_Modifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifier);
  auto t = new TModifiers;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TModifiersV::Modifier;
  t->oneNt = true;
  t->modifier = dynamic_cast<TModifier *>((*stack)[n - 1]);
  assert(t->modifier);
  stack->pop_back();
  stack->push_back(t);
}

// Modifiers -> Modifiers Modifier 
void ptModifiers_ModifiersModifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifier);
  auto t = new TModifiers;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TModifiersV::ModifiersModifier;
  t->oneNt = false;
  t->modifiers = dynamic_cast<TModifiers *>((*stack)[n - 2]);
  assert(t->modifiers);
  t->modifier = dynamic_cast<TModifier *>((*stack)[n - 1]);
  assert(t->modifier);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// Modifier -> public 
void ptModifier_Public(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TModifier;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TModifierV::Public;
  t->oneNt = false;
  stack->push_back(t);
}

// Modifier -> protected 
void ptModifier_Protected(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TModifier;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TModifierV::Protected;
  t->oneNt = false;
  stack->push_back(t);
}

// Modifier -> static 
void ptModifier_Static(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TModifier;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TModifierV::Static;
  t->oneNt = false;
  stack->push_back(t);
}

// Modifier -> abstract 
void ptModifier_abstract(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TModifier;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TModifierV::abstract;
  t->oneNt = false;
  stack->push_back(t);
}

// Modifier -> final 
void ptModifier_final(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TModifier;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TModifierV::final;
  t->oneNt = false;
  stack->push_back(t);
}

// Modifier -> native 
void ptModifier_native(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TModifier;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TModifierV::native;
  t->oneNt = false;
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier ClassBody 
void ptClassDeclaration_ModifiersClassIdentifierClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBody);
  auto t = new TClassDeclaration;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TClassDeclarationV::ModifiersClassIdentifierClassBody;
  t->oneNt = false;
  t->modifiers = dynamic_cast<TModifiers *>((*stack)[n - 3]);
  assert(t->modifiers);
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->classBody = dynamic_cast<TClassBody *>((*stack)[n - 1]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier extends ClassType ClassBody 
void ptClassDeclaration_ModifiersClassIdentifierextendsClassTypeClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 4);
  assert((*stack)[n - 4]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 3]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassType);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBody);
  auto t = new TClassDeclaration;
  ptSetTopParents(stack, 4, t);
  ptPopulateChildrenList(t, *stack, 4);
  t->v = TClassDeclarationV::ModifiersClassIdentifierextendsClassTypeClassBody;
  t->oneNt = false;
  t->modifiers = dynamic_cast<TModifiers *>((*stack)[n - 4]);
  assert(t->modifiers);
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 3]);
  assert(t->identifier);
  t->classType = dynamic_cast<TClassType *>((*stack)[n - 2]);
  assert(t->classType);
  t->classBody = dynamic_cast<TClassBody *>((*stack)[n - 1]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier implements InterfaceTypeList ClassBody 
void ptClassDeclaration_ModifiersClassIdentifierimplementsInterfaceTypeListClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 4);
  assert((*stack)[n - 4]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 3]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceTypeList);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBody);
  auto t = new TClassDeclaration;
  ptSetTopParents(stack, 4, t);
  ptPopulateChildrenList(t, *stack, 4);
  t->v = TClassDeclarationV::ModifiersClassIdentifierimplementsInterfaceTypeListClassBody;
  t->oneNt = false;
  t->modifiers = dynamic_cast<TModifiers *>((*stack)[n - 4]);
  assert(t->modifiers);
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 3]);
  assert(t->identifier);
  t->interfaceTypeList = dynamic_cast<TInterfaceTypeList *>((*stack)[n - 2]);
  assert(t->interfaceTypeList);
  t->classBody = dynamic_cast<TClassBody *>((*stack)[n - 1]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier extends ClassType implements InterfaceTypeList ClassBody 
void ptClassDeclaration_ModifiersClassIdentifierextendsClassTypeimplementsInterfaceTypeListClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 5);
  assert((*stack)[n - 5]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 4]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 3]->type == NonTerminalType::ClassType);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceTypeList);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBody);
  auto t = new TClassDeclaration;
  ptSetTopParents(stack, 5, t);
  ptPopulateChildrenList(t, *stack, 5);
  t->v = TClassDeclarationV::ModifiersClassIdentifierextendsClassTypeimplementsInterfaceTypeListClassBody;
  t->oneNt = false;
  t->modifiers = dynamic_cast<TModifiers *>((*stack)[n - 5]);
  assert(t->modifiers);
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 4]);
  assert(t->identifier);
  t->classType = dynamic_cast<TClassType *>((*stack)[n - 3]);
  assert(t->classType);
  t->interfaceTypeList = dynamic_cast<TInterfaceTypeList *>((*stack)[n - 2]);
  assert(t->interfaceTypeList);
  t->classBody = dynamic_cast<TClassBody *>((*stack)[n - 1]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceTypeList -> InterfaceType 
void ptInterfaceTypeList_InterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceType);
  auto t = new TInterfaceTypeList;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TInterfaceTypeListV::InterfaceType;
  t->oneNt = true;
  t->interfaceType = dynamic_cast<TInterfaceType *>((*stack)[n - 1]);
  assert(t->interfaceType);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceTypeList -> InterfaceTypeList , InterfaceType 
void ptInterfaceTypeList_InterfaceTypeListComInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceTypeList);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceType);
  auto t = new TInterfaceTypeList;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TInterfaceTypeListV::InterfaceTypeListComInterfaceType;
  t->oneNt = false;
  t->interfaceTypeList = dynamic_cast<TInterfaceTypeList *>((*stack)[n - 2]);
  assert(t->interfaceTypeList);
  t->interfaceType = dynamic_cast<TInterfaceType *>((*stack)[n - 1]);
  assert(t->interfaceType);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassBody -> { } 
void ptClassBody_LCBrRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TClassBody;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TClassBodyV::LCBrRCBr;
  t->oneNt = false;
  stack->push_back(t);
}

// ClassBody -> { ClassMemberDeclarations } 
void ptClassBody_LCBrClassMemberDeclarationsRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassMemberDeclarations);
  auto t = new TClassBody;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassBodyV::LCBrClassMemberDeclarationsRCBr;
  t->oneNt = false;
  t->classMemberDeclarations = dynamic_cast<TClassMemberDeclarations *>((*stack)[n - 1]);
  assert(t->classMemberDeclarations);
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclarations -> ClassMemberDeclaration 
void ptClassMemberDeclarations_ClassMemberDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassMemberDeclaration);
  auto t = new TClassMemberDeclarations;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassMemberDeclarationsV::ClassMemberDeclaration;
  t->oneNt = true;
  t->classMemberDeclaration = dynamic_cast<TClassMemberDeclaration *>((*stack)[n - 1]);
  assert(t->classMemberDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclarations -> ClassMemberDeclarations ClassMemberDeclaration 
void ptClassMemberDeclarations_ClassMemberDeclarationsClassMemberDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassMemberDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassMemberDeclaration);
  auto t = new TClassMemberDeclarations;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TClassMemberDeclarationsV::ClassMemberDeclarationsClassMemberDeclaration;
  t->oneNt = false;
  t->classMemberDeclarations = dynamic_cast<TClassMemberDeclarations *>((*stack)[n - 2]);
  assert(t->classMemberDeclarations);
  t->classMemberDeclaration = dynamic_cast<TClassMemberDeclaration *>((*stack)[n - 1]);
  assert(t->classMemberDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclaration -> FieldDeclaration 
void ptClassMemberDeclaration_FieldDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FieldDeclaration);
  auto t = new TClassMemberDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassMemberDeclarationV::FieldDeclaration;
  t->oneNt = true;
  t->fieldDeclaration = dynamic_cast<TFieldDeclaration *>((*stack)[n - 1]);
  assert(t->fieldDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclaration -> MethodDeclaration 
void ptClassMemberDeclaration_MethodDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclaration);
  auto t = new TClassMemberDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassMemberDeclarationV::MethodDeclaration;
  t->oneNt = true;
  t->methodDeclaration = dynamic_cast<TMethodDeclaration *>((*stack)[n - 1]);
  assert(t->methodDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclaration -> ConstructorDeclaration 
void ptClassMemberDeclaration_ConstructorDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ConstructorDeclaration);
  auto t = new TClassMemberDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassMemberDeclarationV::ConstructorDeclaration;
  t->oneNt = true;
  t->constructorDeclaration = dynamic_cast<TConstructorDeclaration *>((*stack)[n - 1]);
  assert(t->constructorDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// FieldDeclaration -> Modifiers Type VariableDeclarator ; 
void ptFieldDeclaration_ModifiersTypeVariableDeclaratorSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableDeclarator);
  auto t = new TFieldDeclaration;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TFieldDeclarationV::ModifiersTypeVariableDeclaratorSCol;
  t->oneNt = false;
  t->modifiers = dynamic_cast<TModifiers *>((*stack)[n - 3]);
  assert(t->modifiers);
  t->type = dynamic_cast<TType *>((*stack)[n - 2]);
  assert(t->type);
  t->variableDeclarator = dynamic_cast<TVariableDeclarator *>((*stack)[n - 1]);
  assert(t->variableDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// VariableDeclarator -> Identifier 
void ptVariableDeclarator_Identifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TVariableDeclarator;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TVariableDeclaratorV::Identifier;
  t->oneNt = false;
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->push_back(t);
}

// VariableDeclarator -> Identifier = Expression 
void ptVariableDeclarator_IdentifierEqExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TVariableDeclarator;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TVariableDeclaratorV::IdentifierEqExpression;
  t->oneNt = false;
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodDeclaration -> MethodHeader MethodBody 
void ptMethodDeclaration_MethodHeaderMethodBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::MethodHeader);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodBody);
  auto t = new TMethodDeclaration;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMethodDeclarationV::MethodHeaderMethodBody;
  t->oneNt = false;
  t->methodHeader = dynamic_cast<TMethodHeader *>((*stack)[n - 2]);
  assert(t->methodHeader);
  t->methodBody = dynamic_cast<TMethodBody *>((*stack)[n - 1]);
  assert(t->methodBody);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> Type MethodDeclarator 
void ptMethodHeader_TypeMethodDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclarator);
  auto t = new TMethodHeader;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMethodHeaderV::TypeMethodDeclarator;
  t->oneNt = false;
  t->type = dynamic_cast<TType *>((*stack)[n - 2]);
  assert(t->type);
  t->methodDeclarator = dynamic_cast<TMethodDeclarator *>((*stack)[n - 1]);
  assert(t->methodDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> Modifiers Type MethodDeclarator 
void ptMethodHeader_ModifiersTypeMethodDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclarator);
  auto t = new TMethodHeader;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TMethodHeaderV::ModifiersTypeMethodDeclarator;
  t->oneNt = false;
  t->modifiers = dynamic_cast<TModifiers *>((*stack)[n - 3]);
  assert(t->modifiers);
  t->type = dynamic_cast<TType *>((*stack)[n - 2]);
  assert(t->type);
  t->methodDeclarator = dynamic_cast<TMethodDeclarator *>((*stack)[n - 1]);
  assert(t->methodDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> void MethodDeclarator 
void ptMethodHeader_VoidMethodDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclarator);
  auto t = new TMethodHeader;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TMethodHeaderV::VoidMethodDeclarator;
  t->oneNt = false;
  t->methodDeclarator = dynamic_cast<TMethodDeclarator *>((*stack)[n - 1]);
  assert(t->methodDeclarator);
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> Modifiers void MethodDeclarator 
void ptMethodHeader_ModifiersVoidMethodDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclarator);
  auto t = new TMethodHeader;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMethodHeaderV::ModifiersVoidMethodDeclarator;
  t->oneNt = false;
  t->modifiers = dynamic_cast<TModifiers *>((*stack)[n - 2]);
  assert(t->modifiers);
  t->methodDeclarator = dynamic_cast<TMethodDeclarator *>((*stack)[n - 1]);
  assert(t->methodDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodDeclarator -> Identifier ( ) 
void ptMethodDeclarator_IdentifierLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TMethodDeclarator;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TMethodDeclaratorV::IdentifierLParRPar;
  t->oneNt = false;
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->push_back(t);
}

// MethodDeclarator -> Identifier ( FormalParameterList ) 
void ptMethodDeclarator_IdentifierLParFormalParameterListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameterList);
  auto t = new TMethodDeclarator;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMethodDeclaratorV::IdentifierLParFormalParameterListRPar;
  t->oneNt = false;
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->formalParameterList = dynamic_cast<TFormalParameterList *>((*stack)[n - 1]);
  assert(t->formalParameterList);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// FormalParameterList -> FormalParameter 
void ptFormalParameterList_FormalParameter(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameter);
  auto t = new TFormalParameterList;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TFormalParameterListV::FormalParameter;
  t->oneNt = true;
  t->formalParameter = dynamic_cast<TFormalParameter *>((*stack)[n - 1]);
  assert(t->formalParameter);
  stack->pop_back();
  stack->push_back(t);
}

// FormalParameterList -> FormalParameterList , FormalParameter 
void ptFormalParameterList_FormalParameterListComFormalParameter(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::FormalParameterList);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameter);
  auto t = new TFormalParameterList;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TFormalParameterListV::FormalParameterListComFormalParameter;
  t->oneNt = false;
  t->formalParameterList = dynamic_cast<TFormalParameterList *>((*stack)[n - 2]);
  assert(t->formalParameterList);
  t->formalParameter = dynamic_cast<TFormalParameter *>((*stack)[n - 1]);
  assert(t->formalParameter);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// FormalParameter -> Type Identifier 
void ptFormalParameter_TypeIdentifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TFormalParameter;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TFormalParameterV::TypeIdentifier;
  t->oneNt = false;
  t->type = dynamic_cast<TType *>((*stack)[n - 2]);
  assert(t->type);
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodBody -> Block 
void ptMethodBody_Block(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Block);
  auto t = new TMethodBody;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TMethodBodyV::Block;
  t->oneNt = true;
  t->block = dynamic_cast<TBlock *>((*stack)[n - 1]);
  assert(t->block);
  stack->pop_back();
  stack->push_back(t);
}

// MethodBody -> AbstractMethodBody 
void ptMethodBody_AbstractMethodBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AbstractMethodBody);
  auto t = new TMethodBody;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TMethodBodyV::AbstractMethodBody;
  t->oneNt = true;
  t->abstractMethodBody = dynamic_cast<TAbstractMethodBody *>((*stack)[n - 1]);
  assert(t->abstractMethodBody);
  stack->pop_back();
  stack->push_back(t);
}

// AbstractMethodBody -> ; 
void ptAbstractMethodBody_SCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TAbstractMethodBody;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TAbstractMethodBodyV::SCol;
  t->oneNt = false;
  stack->push_back(t);
}

// ConstructorDeclaration -> Modifiers ConstructorDeclarator Block 
void ptConstructorDeclaration_ModifiersConstructorDeclaratorBlock(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::ConstructorDeclarator);
  assert((*stack)[n - 1]->type == NonTerminalType::Block);
  auto t = new TConstructorDeclaration;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TConstructorDeclarationV::ModifiersConstructorDeclaratorBlock;
  t->oneNt = false;
  t->modifiers = dynamic_cast<TModifiers *>((*stack)[n - 3]);
  assert(t->modifiers);
  t->constructorDeclarator = dynamic_cast<TConstructorDeclarator *>((*stack)[n - 2]);
  assert(t->constructorDeclarator);
  t->block = dynamic_cast<TBlock *>((*stack)[n - 1]);
  assert(t->block);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ConstructorDeclarator -> Identifier ( ) 
void ptConstructorDeclarator_IdentifierLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TConstructorDeclarator;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TConstructorDeclaratorV::IdentifierLParRPar;
  t->oneNt = false;
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->push_back(t);
}

// ConstructorDeclarator -> Identifier ( FormalParameterList ) 
void ptConstructorDeclarator_IdentifierLParFormalParameterListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameterList);
  auto t = new TConstructorDeclarator;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TConstructorDeclaratorV::IdentifierLParFormalParameterListRPar;
  t->oneNt = false;
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->formalParameterList = dynamic_cast<TFormalParameterList *>((*stack)[n - 1]);
  assert(t->formalParameterList);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> interface Identifier InterfaceBody 
void ptInterfaceDeclaration_interfaceIdentifierInterfaceBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceBody);
  auto t = new TInterfaceDeclaration;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TInterfaceDeclarationV::interfaceIdentifierInterfaceBody;
  t->oneNt = false;
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->interfaceBody = dynamic_cast<TInterfaceBody *>((*stack)[n - 1]);
  assert(t->interfaceBody);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> Modifiers interface Identifier InterfaceBody 
void ptInterfaceDeclaration_ModifiersinterfaceIdentifierInterfaceBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceBody);
  auto t = new TInterfaceDeclaration;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TInterfaceDeclarationV::ModifiersinterfaceIdentifierInterfaceBody;
  t->oneNt = false;
  t->modifiers = dynamic_cast<TModifiers *>((*stack)[n - 3]);
  assert(t->modifiers);
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->interfaceBody = dynamic_cast<TInterfaceBody *>((*stack)[n - 1]);
  assert(t->interfaceBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> interface Identifier ExtendsInterfaces InterfaceBody 
void ptInterfaceDeclaration_interfaceIdentifierExtendsInterfacesInterfaceBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 2]->type == NonTerminalType::ExtendsInterfaces);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceBody);
  auto t = new TInterfaceDeclaration;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TInterfaceDeclarationV::interfaceIdentifierExtendsInterfacesInterfaceBody;
  t->oneNt = false;
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 3]);
  assert(t->identifier);
  t->extendsInterfaces = dynamic_cast<TExtendsInterfaces *>((*stack)[n - 2]);
  assert(t->extendsInterfaces);
  t->interfaceBody = dynamic_cast<TInterfaceBody *>((*stack)[n - 1]);
  assert(t->interfaceBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> Modifiers interface Identifier ExtendsInterfaces InterfaceBody 
void ptInterfaceDeclaration_ModifiersinterfaceIdentifierExtendsInterfacesInterfaceBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 4);
  assert((*stack)[n - 4]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 3]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 2]->type == NonTerminalType::ExtendsInterfaces);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceBody);
  auto t = new TInterfaceDeclaration;
  ptSetTopParents(stack, 4, t);
  ptPopulateChildrenList(t, *stack, 4);
  t->v = TInterfaceDeclarationV::ModifiersinterfaceIdentifierExtendsInterfacesInterfaceBody;
  t->oneNt = false;
  t->modifiers = dynamic_cast<TModifiers *>((*stack)[n - 4]);
  assert(t->modifiers);
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 3]);
  assert(t->identifier);
  t->extendsInterfaces = dynamic_cast<TExtendsInterfaces *>((*stack)[n - 2]);
  assert(t->extendsInterfaces);
  t->interfaceBody = dynamic_cast<TInterfaceBody *>((*stack)[n - 1]);
  assert(t->interfaceBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ExtendsInterfaces -> extends InterfaceType 
void ptExtendsInterfaces_extendsInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceType);
  auto t = new TExtendsInterfaces;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TExtendsInterfacesV::extendsInterfaceType;
  t->oneNt = false;
  t->interfaceType = dynamic_cast<TInterfaceType *>((*stack)[n - 1]);
  assert(t->interfaceType);
  stack->pop_back();
  stack->push_back(t);
}

// ExtendsInterfaces -> ExtendsInterfaces , InterfaceType 
void ptExtendsInterfaces_ExtendsInterfacesComInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ExtendsInterfaces);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceType);
  auto t = new TExtendsInterfaces;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TExtendsInterfacesV::ExtendsInterfacesComInterfaceType;
  t->oneNt = false;
  t->extendsInterfaces = dynamic_cast<TExtendsInterfaces *>((*stack)[n - 2]);
  assert(t->extendsInterfaces);
  t->interfaceType = dynamic_cast<TInterfaceType *>((*stack)[n - 1]);
  assert(t->interfaceType);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceBody -> { } 
void ptInterfaceBody_LCBrRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TInterfaceBody;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TInterfaceBodyV::LCBrRCBr;
  t->oneNt = false;
  stack->push_back(t);
}

// InterfaceBody -> { InterfaceMemberDeclarations } 
void ptInterfaceBody_LCBrInterfaceMemberDeclarationsRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceMemberDeclarations);
  auto t = new TInterfaceBody;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TInterfaceBodyV::LCBrInterfaceMemberDeclarationsRCBr;
  t->oneNt = false;
  t->interfaceMemberDeclarations = dynamic_cast<TInterfaceMemberDeclarations *>((*stack)[n - 1]);
  assert(t->interfaceMemberDeclarations);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceMemberDeclarations -> InterfaceMemberDeclaration 
void ptInterfaceMemberDeclarations_InterfaceMemberDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceMemberDeclaration);
  auto t = new TInterfaceMemberDeclarations;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TInterfaceMemberDeclarationsV::InterfaceMemberDeclaration;
  t->oneNt = true;
  t->interfaceMemberDeclaration = dynamic_cast<TInterfaceMemberDeclaration *>((*stack)[n - 1]);
  assert(t->interfaceMemberDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceMemberDeclarations -> InterfaceMemberDeclarations InterfaceMemberDeclaration 
void ptInterfaceMemberDeclarations_InterfaceMemberDeclarationsInterfaceMemberDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceMemberDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceMemberDeclaration);
  auto t = new TInterfaceMemberDeclarations;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TInterfaceMemberDeclarationsV::InterfaceMemberDeclarationsInterfaceMemberDeclaration;
  t->oneNt = false;
  t->interfaceMemberDeclarations = dynamic_cast<TInterfaceMemberDeclarations *>((*stack)[n - 2]);
  assert(t->interfaceMemberDeclarations);
  t->interfaceMemberDeclaration = dynamic_cast<TInterfaceMemberDeclaration *>((*stack)[n - 1]);
  assert(t->interfaceMemberDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceMemberDeclaration -> AbstractMethodDeclaration 
void ptInterfaceMemberDeclaration_AbstractMethodDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AbstractMethodDeclaration);
  auto t = new TInterfaceMemberDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TInterfaceMemberDeclarationV::AbstractMethodDeclaration;
  t->oneNt = true;
  t->abstractMethodDeclaration = dynamic_cast<TAbstractMethodDeclaration *>((*stack)[n - 1]);
  assert(t->abstractMethodDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// AbstractMethodDeclaration -> MethodHeader ; 
void ptAbstractMethodDeclaration_MethodHeaderSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodHeader);
  auto t = new TAbstractMethodDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TAbstractMethodDeclarationV::MethodHeaderSCol;
  t->oneNt = false;
  t->methodHeader = dynamic_cast<TMethodHeader *>((*stack)[n - 1]);
  assert(t->methodHeader);
  stack->pop_back();
  stack->push_back(t);
}

// Block -> { } 
void ptBlock_LCBrRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TBlock;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TBlockV::LCBrRCBr;
  t->oneNt = false;
  stack->push_back(t);
}

// Block -> { BlockStatements } 
void ptBlock_LCBrBlockStatementsRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::BlockStatements);
  auto t = new TBlock;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TBlockV::LCBrBlockStatementsRCBr;
  t->oneNt = false;
  t->blockStatements = dynamic_cast<TBlockStatements *>((*stack)[n - 1]);
  assert(t->blockStatements);
  stack->pop_back();
  stack->push_back(t);
}

// BlockStatements -> BlockStatement 
void ptBlockStatements_BlockStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::BlockStatement);
  auto t = new TBlockStatements;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TBlockStatementsV::BlockStatement;
  t->oneNt = true;
  t->blockStatement = dynamic_cast<TBlockStatement *>((*stack)[n - 1]);
  assert(t->blockStatement);
  stack->pop_back();
  stack->push_back(t);
}

// BlockStatements -> BlockStatements BlockStatement 
void ptBlockStatements_BlockStatementsBlockStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::BlockStatements);
  assert((*stack)[n - 1]->type == NonTerminalType::BlockStatement);
  auto t = new TBlockStatements;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TBlockStatementsV::BlockStatementsBlockStatement;
  t->oneNt = false;
  t->blockStatements = dynamic_cast<TBlockStatements *>((*stack)[n - 2]);
  assert(t->blockStatements);
  t->blockStatement = dynamic_cast<TBlockStatement *>((*stack)[n - 1]);
  assert(t->blockStatement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// BlockStatement -> LocalVariableDeclarationStatement 
void ptBlockStatement_LocalVariableDeclarationStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::LocalVariableDeclarationStatement);
  auto t = new TBlockStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TBlockStatementV::LocalVariableDeclarationStatement;
  t->oneNt = true;
  t->localVariableDeclarationStatement = dynamic_cast<TLocalVariableDeclarationStatement *>((*stack)[n - 1]);
  assert(t->localVariableDeclarationStatement);
  stack->pop_back();
  stack->push_back(t);
}

// BlockStatement -> Statement 
void ptBlockStatement_Statement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TBlockStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TBlockStatementV::Statement;
  t->oneNt = true;
  t->statement = dynamic_cast<TStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->push_back(t);
}

// LocalVariableDeclarationStatement -> LocalVariableDeclaration ; 
void ptLocalVariableDeclarationStatement_LocalVariableDeclarationSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::LocalVariableDeclaration);
  auto t = new TLocalVariableDeclarationStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLocalVariableDeclarationStatementV::LocalVariableDeclarationSCol;
  t->oneNt = false;
  t->localVariableDeclaration = dynamic_cast<TLocalVariableDeclaration *>((*stack)[n - 1]);
  assert(t->localVariableDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// LocalVariableDeclaration -> Type VariableDeclarator 
void ptLocalVariableDeclaration_TypeVariableDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableDeclarator);
  auto t = new TLocalVariableDeclaration;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TLocalVariableDeclarationV::TypeVariableDeclarator;
  t->oneNt = false;
  t->type = dynamic_cast<TType *>((*stack)[n - 2]);
  assert(t->type);
  t->variableDeclarator = dynamic_cast<TVariableDeclarator *>((*stack)[n - 1]);
  assert(t->variableDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> StatementWithoutTrailingSubstatement 
void ptStatement_StatementWithoutTrailingSubstatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementWithoutTrailingSubstatement);
  auto t = new TStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementV::StatementWithoutTrailingSubstatement;
  t->oneNt = true;
  t->statementWithoutTrailingSubstatement = dynamic_cast<TStatementWithoutTrailingSubstatement *>((*stack)[n - 1]);
  assert(t->statementWithoutTrailingSubstatement);
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> IfThenStatement 
void ptStatement_IfThenStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::IfThenStatement);
  auto t = new TStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementV::IfThenStatement;
  t->oneNt = true;
  t->ifThenStatement = dynamic_cast<TIfThenStatement *>((*stack)[n - 1]);
  assert(t->ifThenStatement);
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> IfThenElseStatement 
void ptStatement_IfThenElseStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::IfThenElseStatement);
  auto t = new TStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementV::IfThenElseStatement;
  t->oneNt = true;
  t->ifThenElseStatement = dynamic_cast<TIfThenElseStatement *>((*stack)[n - 1]);
  assert(t->ifThenElseStatement);
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> WhileStatement 
void ptStatement_WhileStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::WhileStatement);
  auto t = new TStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementV::WhileStatement;
  t->oneNt = true;
  t->whileStatement = dynamic_cast<TWhileStatement *>((*stack)[n - 1]);
  assert(t->whileStatement);
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> ForStatement 
void ptStatement_ForStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ForStatement);
  auto t = new TStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementV::ForStatement;
  t->oneNt = true;
  t->forStatement = dynamic_cast<TForStatement *>((*stack)[n - 1]);
  assert(t->forStatement);
  stack->pop_back();
  stack->push_back(t);
}

// StatementNoShortIf -> StatementWithoutTrailingSubstatement 
void ptStatementNoShortIf_StatementWithoutTrailingSubstatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementWithoutTrailingSubstatement);
  auto t = new TStatementNoShortIf;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementNoShortIfV::StatementWithoutTrailingSubstatement;
  t->oneNt = true;
  t->statementWithoutTrailingSubstatement = dynamic_cast<TStatementWithoutTrailingSubstatement *>((*stack)[n - 1]);
  assert(t->statementWithoutTrailingSubstatement);
  stack->pop_back();
  stack->push_back(t);
}

// StatementNoShortIf -> IfThenElseStatementNoShortIf 
void ptStatementNoShortIf_IfThenElseStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::IfThenElseStatementNoShortIf);
  auto t = new TStatementNoShortIf;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementNoShortIfV::IfThenElseStatementNoShortIf;
  t->oneNt = true;
  t->ifThenElseStatementNoShortIf = dynamic_cast<TIfThenElseStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->ifThenElseStatementNoShortIf);
  stack->pop_back();
  stack->push_back(t);
}

// StatementNoShortIf -> WhileStatementNoShortIf 
void ptStatementNoShortIf_WhileStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::WhileStatementNoShortIf);
  auto t = new TStatementNoShortIf;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementNoShortIfV::WhileStatementNoShortIf;
  t->oneNt = true;
  t->whileStatementNoShortIf = dynamic_cast<TWhileStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->whileStatementNoShortIf);
  stack->pop_back();
  stack->push_back(t);
}

// StatementNoShortIf -> ForStatementNoShortIf 
void ptStatementNoShortIf_ForStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ForStatementNoShortIf);
  auto t = new TStatementNoShortIf;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementNoShortIfV::ForStatementNoShortIf;
  t->oneNt = true;
  t->forStatementNoShortIf = dynamic_cast<TForStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->forStatementNoShortIf);
  stack->pop_back();
  stack->push_back(t);
}

// StatementWithoutTrailingSubstatement -> Block 
void ptStatementWithoutTrailingSubstatement_Block(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Block);
  auto t = new TStatementWithoutTrailingSubstatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementWithoutTrailingSubstatementV::Block;
  t->oneNt = true;
  t->block = dynamic_cast<TBlock *>((*stack)[n - 1]);
  assert(t->block);
  stack->pop_back();
  stack->push_back(t);
}

// StatementWithoutTrailingSubstatement -> ExpressionStatement 
void ptStatementWithoutTrailingSubstatement_ExpressionStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ExpressionStatement);
  auto t = new TStatementWithoutTrailingSubstatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementWithoutTrailingSubstatementV::ExpressionStatement;
  t->oneNt = true;
  t->expressionStatement = dynamic_cast<TExpressionStatement *>((*stack)[n - 1]);
  assert(t->expressionStatement);
  stack->pop_back();
  stack->push_back(t);
}

// StatementWithoutTrailingSubstatement -> ReturnStatement 
void ptStatementWithoutTrailingSubstatement_ReturnStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ReturnStatement);
  auto t = new TStatementWithoutTrailingSubstatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementWithoutTrailingSubstatementV::ReturnStatement;
  t->oneNt = true;
  t->returnStatement = dynamic_cast<TReturnStatement *>((*stack)[n - 1]);
  assert(t->returnStatement);
  stack->pop_back();
  stack->push_back(t);
}

// ExpressionStatement -> ; 
void ptExpressionStatement_SCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TExpressionStatement;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TExpressionStatementV::SCol;
  t->oneNt = false;
  stack->push_back(t);
}

// ExpressionStatement -> StatementExpression ; 
void ptExpressionStatement_StatementExpressionSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementExpression);
  auto t = new TExpressionStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TExpressionStatementV::StatementExpressionSCol;
  t->oneNt = false;
  t->statementExpression = dynamic_cast<TStatementExpression *>((*stack)[n - 1]);
  assert(t->statementExpression);
  stack->pop_back();
  stack->push_back(t);
}

// StatementExpression -> Assignment 
void ptStatementExpression_Assignment(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Assignment);
  auto t = new TStatementExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementExpressionV::Assignment;
  t->oneNt = true;
  t->assignment = dynamic_cast<TAssignment *>((*stack)[n - 1]);
  assert(t->assignment);
  stack->pop_back();
  stack->push_back(t);
}

// StatementExpression -> MethodInvocation 
void ptStatementExpression_MethodInvocation(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodInvocation);
  auto t = new TStatementExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementExpressionV::MethodInvocation;
  t->oneNt = true;
  t->methodInvocation = dynamic_cast<TMethodInvocation *>((*stack)[n - 1]);
  assert(t->methodInvocation);
  stack->pop_back();
  stack->push_back(t);
}

// StatementExpression -> ClassInstanceCreationExpression 
void ptStatementExpression_ClassInstanceCreationExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassInstanceCreationExpression);
  auto t = new TStatementExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementExpressionV::ClassInstanceCreationExpression;
  t->oneNt = true;
  t->classInstanceCreationExpression = dynamic_cast<TClassInstanceCreationExpression *>((*stack)[n - 1]);
  assert(t->classInstanceCreationExpression);
  stack->pop_back();
  stack->push_back(t);
}

// IfThenStatement -> if ( Expression ) Statement 
void ptIfThenStatement_IfLParExpressionRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TIfThenStatement;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TIfThenStatementV::IfLParExpressionRParStatement;
  t->oneNt = false;
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statement = dynamic_cast<TStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// IfThenElseStatement -> if ( Expression ) StatementNoShortIf else Statement 
void ptIfThenElseStatement_IfLParExpressionRParStatementNoShortIfElseStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::StatementNoShortIf);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TIfThenElseStatement;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TIfThenElseStatementV::IfLParExpressionRParStatementNoShortIfElseStatement;
  t->oneNt = false;
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 3]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TStatementNoShortIf *>((*stack)[n - 2]);
  assert(t->statementNoShortIf);
  t->statement = dynamic_cast<TStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// IfThenElseStatementNoShortIf -> if ( Expression ) StatementNoShortIf else StatementNoShortIf 
void ptIfThenElseStatementNoShortIf_IfLParExpressionRParStatementNoShortIfElseStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::StatementNoShortIf);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TIfThenElseStatementNoShortIf;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TIfThenElseStatementNoShortIfV::IfLParExpressionRParStatementNoShortIfElseStatementNoShortIf;
  t->oneNt = false;
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 3]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TStatementNoShortIf *>((*stack)[n - 2]);
  assert(t->statementNoShortIf);
  t->statementNoShortIf2 = dynamic_cast<TStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// WhileStatement -> while ( Expression ) Statement 
void ptWhileStatement_WhileLParExpressionRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TWhileStatement;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TWhileStatementV::WhileLParExpressionRParStatement;
  t->oneNt = false;
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statement = dynamic_cast<TStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// WhileStatementNoShortIf -> while ( Expression ) StatementNoShortIf 
void ptWhileStatementNoShortIf_WhileLParExpressionRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TWhileStatementNoShortIf;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TWhileStatementNoShortIfV::WhileLParExpressionRParStatementNoShortIf;
  t->oneNt = false;
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit ; ) Statement 
void ptForStatement_ForLParForInitSColRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TForStatement;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TForStatementV::ForLParForInitSColRParStatement;
  t->oneNt = false;
  t->forInit = dynamic_cast<TForInit *>((*stack)[n - 2]);
  assert(t->forInit);
  t->statement = dynamic_cast<TStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit Expression ; ) Statement 
void ptForStatement_ForLParForInitExpressionSColRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TForStatement;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TForStatementV::ForLParForInitExpressionSColRParStatement;
  t->oneNt = false;
  t->forInit = dynamic_cast<TForInit *>((*stack)[n - 3]);
  assert(t->forInit);
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statement = dynamic_cast<TStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit ; ForUpdate ) Statement 
void ptForStatement_ForLParForInitSColForUpdateRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TForStatement;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TForStatementV::ForLParForInitSColForUpdateRParStatement;
  t->oneNt = false;
  t->forInit = dynamic_cast<TForInit *>((*stack)[n - 3]);
  assert(t->forInit);
  t->forUpdate = dynamic_cast<TForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statement = dynamic_cast<TStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit Expression ; ForUpdate ) Statement 
void ptForStatement_ForLParForInitExpressionSColForUpdateRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 4);
  assert((*stack)[n - 4]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 3]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TForStatement;
  ptSetTopParents(stack, 4, t);
  ptPopulateChildrenList(t, *stack, 4);
  t->v = TForStatementV::ForLParForInitExpressionSColForUpdateRParStatement;
  t->oneNt = false;
  t->forInit = dynamic_cast<TForInit *>((*stack)[n - 4]);
  assert(t->forInit);
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 3]);
  assert(t->expression);
  t->forUpdate = dynamic_cast<TForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statement = dynamic_cast<TStatement *>((*stack)[n - 1]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit ; ) StatementNoShortIf 
void ptForStatementNoShortIf_ForLParForInitSColRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TForStatementNoShortIf;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TForStatementNoShortIfV::ForLParForInitSColRParStatementNoShortIf;
  t->oneNt = false;
  t->forInit = dynamic_cast<TForInit *>((*stack)[n - 2]);
  assert(t->forInit);
  t->statementNoShortIf = dynamic_cast<TStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit Expression ; ) StatementNoShortIf 
void ptForStatementNoShortIf_ForLParForInitExpressionSColRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TForStatementNoShortIf;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TForStatementNoShortIfV::ForLParForInitExpressionSColRParStatementNoShortIf;
  t->oneNt = false;
  t->forInit = dynamic_cast<TForInit *>((*stack)[n - 3]);
  assert(t->forInit);
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit ; ForUpdate ) StatementNoShortIf 
void ptForStatementNoShortIf_ForLParForInitSColForUpdateRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TForStatementNoShortIf;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TForStatementNoShortIfV::ForLParForInitSColForUpdateRParStatementNoShortIf;
  t->oneNt = false;
  t->forInit = dynamic_cast<TForInit *>((*stack)[n - 3]);
  assert(t->forInit);
  t->forUpdate = dynamic_cast<TForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statementNoShortIf = dynamic_cast<TStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit Expression ; ForUpdate ) StatementNoShortIf 
void ptForStatementNoShortIf_ForLParForInitExpressionSColForUpdateRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 4);
  assert((*stack)[n - 4]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 3]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TForStatementNoShortIf;
  ptSetTopParents(stack, 4, t);
  ptPopulateChildrenList(t, *stack, 4);
  t->v = TForStatementNoShortIfV::ForLParForInitExpressionSColForUpdateRParStatementNoShortIf;
  t->oneNt = false;
  t->forInit = dynamic_cast<TForInit *>((*stack)[n - 4]);
  assert(t->forInit);
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 3]);
  assert(t->expression);
  t->forUpdate = dynamic_cast<TForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statementNoShortIf = dynamic_cast<TStatementNoShortIf *>((*stack)[n - 1]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForInit -> ExpressionStatement 
void ptForInit_ExpressionStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ExpressionStatement);
  auto t = new TForInit;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TForInitV::ExpressionStatement;
  t->oneNt = true;
  t->expressionStatement = dynamic_cast<TExpressionStatement *>((*stack)[n - 1]);
  assert(t->expressionStatement);
  stack->pop_back();
  stack->push_back(t);
}

// ForInit -> LocalVariableDeclarationStatement 
void ptForInit_LocalVariableDeclarationStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::LocalVariableDeclarationStatement);
  auto t = new TForInit;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TForInitV::LocalVariableDeclarationStatement;
  t->oneNt = true;
  t->localVariableDeclarationStatement = dynamic_cast<TLocalVariableDeclarationStatement *>((*stack)[n - 1]);
  assert(t->localVariableDeclarationStatement);
  stack->pop_back();
  stack->push_back(t);
}

// ForUpdate -> StatementExpression 
void ptForUpdate_StatementExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementExpression);
  auto t = new TForUpdate;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TForUpdateV::StatementExpression;
  t->oneNt = true;
  t->statementExpression = dynamic_cast<TStatementExpression *>((*stack)[n - 1]);
  assert(t->statementExpression);
  stack->pop_back();
  stack->push_back(t);
}

// ReturnStatement -> return ; 
void ptReturnStatement_ReturnSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TReturnStatement;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TReturnStatementV::ReturnSCol;
  t->oneNt = false;
  stack->push_back(t);
}

// ReturnStatement -> return Expression ; 
void ptReturnStatement_ReturnExpressionSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TReturnStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TReturnStatementV::ReturnExpressionSCol;
  t->oneNt = false;
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->push_back(t);
}

// Primary -> PrimaryNoNewArray 
void ptPrimary_PrimaryNoNewArray(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimaryNoNewArray);
  auto t = new TPrimary;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryV::PrimaryNoNewArray;
  t->oneNt = true;
  t->primaryNoNewArray = dynamic_cast<TPrimaryNoNewArray *>((*stack)[n - 1]);
  assert(t->primaryNoNewArray);
  stack->pop_back();
  stack->push_back(t);
}

// Primary -> ArrayCreationExpression 
void ptPrimary_ArrayCreationExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayCreationExpression);
  auto t = new TPrimary;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryV::ArrayCreationExpression;
  t->oneNt = true;
  t->arrayCreationExpression = dynamic_cast<TArrayCreationExpression *>((*stack)[n - 1]);
  assert(t->arrayCreationExpression);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> Literal 
void ptPrimaryNoNewArray_Literal(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Literal);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::Literal;
  t->oneNt = true;
  t->literal = dynamic_cast<TLiteral *>((*stack)[n - 1]);
  assert(t->literal);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> This2 
void ptPrimaryNoNewArray_This2(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::This2);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::This2;
  t->oneNt = true;
  t->this2 = dynamic_cast<TThis2 *>((*stack)[n - 1]);
  assert(t->this2);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> ParenthesizedExpression 
void ptPrimaryNoNewArray_ParenthesizedExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ParenthesizedExpression);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::ParenthesizedExpression;
  t->oneNt = true;
  t->parenthesizedExpression = dynamic_cast<TParenthesizedExpression *>((*stack)[n - 1]);
  assert(t->parenthesizedExpression);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> ClassInstanceCreationExpression 
void ptPrimaryNoNewArray_ClassInstanceCreationExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassInstanceCreationExpression);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::ClassInstanceCreationExpression;
  t->oneNt = true;
  t->classInstanceCreationExpression = dynamic_cast<TClassInstanceCreationExpression *>((*stack)[n - 1]);
  assert(t->classInstanceCreationExpression);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> FieldAccess 
void ptPrimaryNoNewArray_FieldAccess(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FieldAccess);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::FieldAccess;
  t->oneNt = true;
  t->fieldAccess = dynamic_cast<TFieldAccess *>((*stack)[n - 1]);
  assert(t->fieldAccess);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> MethodInvocation 
void ptPrimaryNoNewArray_MethodInvocation(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodInvocation);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::MethodInvocation;
  t->oneNt = true;
  t->methodInvocation = dynamic_cast<TMethodInvocation *>((*stack)[n - 1]);
  assert(t->methodInvocation);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> ArrayAccess 
void ptPrimaryNoNewArray_ArrayAccess(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayAccess);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::ArrayAccess;
  t->oneNt = true;
  t->arrayAccess = dynamic_cast<TArrayAccess *>((*stack)[n - 1]);
  assert(t->arrayAccess);
  stack->pop_back();
  stack->push_back(t);
}

// This2 -> this 
void ptThis2_This2(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TThis2;
  ptSetTopParents(stack, 0, t);
  ptPopulateChildrenList(t, *stack, 0);
  t->v = TThis2V::This2;
  t->oneNt = false;
  stack->push_back(t);
}

// ParenthesizedExpression -> ( Expression ) 
void ptParenthesizedExpression_LParExpressionRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TParenthesizedExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TParenthesizedExpressionV::LParExpressionRPar;
  t->oneNt = false;
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->push_back(t);
}

// ClassInstanceCreationExpression -> new ClassType ( ) 
void ptClassInstanceCreationExpression_NewClassTypeLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassType);
  auto t = new TClassInstanceCreationExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassInstanceCreationExpressionV::NewClassTypeLParRPar;
  t->oneNt = false;
  t->classType = dynamic_cast<TClassType *>((*stack)[n - 1]);
  assert(t->classType);
  stack->pop_back();
  stack->push_back(t);
}

// ClassInstanceCreationExpression -> new ClassType ( ArgumentList ) 
void ptClassInstanceCreationExpression_NewClassTypeLParArgumentListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassType);
  assert((*stack)[n - 1]->type == NonTerminalType::ArgumentList);
  auto t = new TClassInstanceCreationExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TClassInstanceCreationExpressionV::NewClassTypeLParArgumentListRPar;
  t->oneNt = false;
  t->classType = dynamic_cast<TClassType *>((*stack)[n - 2]);
  assert(t->classType);
  t->argumentList = dynamic_cast<TArgumentList *>((*stack)[n - 1]);
  assert(t->argumentList);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArgumentList -> Expression 
void ptArgumentList_Expression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TArgumentList;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TArgumentListV::Expression;
  t->oneNt = true;
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->push_back(t);
}

// ArgumentList -> ArgumentList , Expression 
void ptArgumentList_ArgumentListComExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ArgumentList);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TArgumentList;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TArgumentListV::ArgumentListComExpression;
  t->oneNt = false;
  t->argumentList = dynamic_cast<TArgumentList *>((*stack)[n - 2]);
  assert(t->argumentList);
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayCreationExpression -> new PrimitiveType [ Expression ] 
void ptArrayCreationExpression_NewPrimitiveTypeLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PrimitiveType);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TArrayCreationExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TArrayCreationExpressionV::NewPrimitiveTypeLSBrExpressionRSBr;
  t->oneNt = false;
  t->primitiveType = dynamic_cast<TPrimitiveType *>((*stack)[n - 2]);
  assert(t->primitiveType);
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayCreationExpression -> new ClassOrInterfaceType [ Expression ] 
void ptArrayCreationExpression_NewClassOrInterfaceTypeLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassOrInterfaceType);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TArrayCreationExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TArrayCreationExpressionV::NewClassOrInterfaceTypeLSBrExpressionRSBr;
  t->oneNt = false;
  t->classOrInterfaceType = dynamic_cast<TClassOrInterfaceType *>((*stack)[n - 2]);
  assert(t->classOrInterfaceType);
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// FieldAccess -> Primary . Identifier 
void ptFieldAccess_PrimaryDotIdentifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Primary);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TFieldAccess;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TFieldAccessV::PrimaryDotIdentifier;
  t->oneNt = false;
  t->primary = dynamic_cast<TPrimary *>((*stack)[n - 2]);
  assert(t->primary);
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Name ( ) 
void ptMethodInvocation_NameLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TMethodInvocation;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TMethodInvocationV::NameLParRPar;
  t->oneNt = false;
  t->name = dynamic_cast<TName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Name ( ArgumentList ) 
void ptMethodInvocation_NameLParArgumentListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Name);
  assert((*stack)[n - 1]->type == NonTerminalType::ArgumentList);
  auto t = new TMethodInvocation;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMethodInvocationV::NameLParArgumentListRPar;
  t->oneNt = false;
  t->name = dynamic_cast<TName *>((*stack)[n - 2]);
  assert(t->name);
  t->argumentList = dynamic_cast<TArgumentList *>((*stack)[n - 1]);
  assert(t->argumentList);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Primary . Identifier ( ) 
void ptMethodInvocation_PrimaryDotIdentifierLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Primary);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TMethodInvocation;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMethodInvocationV::PrimaryDotIdentifierLParRPar;
  t->oneNt = false;
  t->primary = dynamic_cast<TPrimary *>((*stack)[n - 2]);
  assert(t->primary);
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 1]);
  assert(t->identifier);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Primary . Identifier ( ArgumentList ) 
void ptMethodInvocation_PrimaryDotIdentifierLParArgumentListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 3]->type == NonTerminalType::Primary);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::ArgumentList);
  auto t = new TMethodInvocation;
  ptSetTopParents(stack, 3, t);
  ptPopulateChildrenList(t, *stack, 3);
  t->v = TMethodInvocationV::PrimaryDotIdentifierLParArgumentListRPar;
  t->oneNt = false;
  t->primary = dynamic_cast<TPrimary *>((*stack)[n - 3]);
  assert(t->primary);
  t->identifier = dynamic_cast<TIdentifier *>((*stack)[n - 2]);
  assert(t->identifier);
  t->argumentList = dynamic_cast<TArgumentList *>((*stack)[n - 1]);
  assert(t->argumentList);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayAccess -> Name [ Expression ] 
void ptArrayAccess_NameLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Name);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TArrayAccess;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TArrayAccessV::NameLSBrExpressionRSBr;
  t->oneNt = false;
  t->name = dynamic_cast<TName *>((*stack)[n - 2]);
  assert(t->name);
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayAccess -> PrimaryNoNewArray [ Expression ] 
void ptArrayAccess_PrimaryNoNewArrayLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PrimaryNoNewArray);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TArrayAccess;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TArrayAccessV::PrimaryNoNewArrayLSBrExpressionRSBr;
  t->oneNt = false;
  t->primaryNoNewArray = dynamic_cast<TPrimaryNoNewArray *>((*stack)[n - 2]);
  assert(t->primaryNoNewArray);
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpression -> - UnaryExpression 
void ptUnaryExpression_MinusUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TUnaryExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TUnaryExpressionV::MinusUnaryExpression;
  t->oneNt = false;
  t->unaryExpression = dynamic_cast<TUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpression -> UnaryExpressionNotPlusMinus 
void ptUnaryExpression_UnaryExpressionNotPlusMinus(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpressionNotPlusMinus);
  auto t = new TUnaryExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TUnaryExpressionV::UnaryExpressionNotPlusMinus;
  t->oneNt = true;
  t->unaryExpressionNotPlusMinus = dynamic_cast<TUnaryExpressionNotPlusMinus *>((*stack)[n - 1]);
  assert(t->unaryExpressionNotPlusMinus);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> Primary 
void ptUnaryExpressionNotPlusMinus_Primary(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Primary);
  auto t = new TUnaryExpressionNotPlusMinus;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TUnaryExpressionNotPlusMinusV::Primary;
  t->oneNt = true;
  t->primary = dynamic_cast<TPrimary *>((*stack)[n - 1]);
  assert(t->primary);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> Name 
void ptUnaryExpressionNotPlusMinus_Name(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TUnaryExpressionNotPlusMinus;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TUnaryExpressionNotPlusMinusV::Name;
  t->oneNt = true;
  t->name = dynamic_cast<TName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> ! UnaryExpression 
void ptUnaryExpressionNotPlusMinus_BangUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TUnaryExpressionNotPlusMinus;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TUnaryExpressionNotPlusMinusV::BangUnaryExpression;
  t->oneNt = false;
  t->unaryExpression = dynamic_cast<TUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> CastExpression 
void ptUnaryExpressionNotPlusMinus_CastExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::CastExpression);
  auto t = new TUnaryExpressionNotPlusMinus;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TUnaryExpressionNotPlusMinusV::CastExpression;
  t->oneNt = true;
  t->castExpression = dynamic_cast<TCastExpression *>((*stack)[n - 1]);
  assert(t->castExpression);
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( PrimitiveType ) UnaryExpression 
void ptCastExpression_LParPrimitiveTypeRParUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PrimitiveType);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TCastExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCastExpressionV::LParPrimitiveTypeRParUnaryExpression;
  t->oneNt = false;
  t->primitiveType = dynamic_cast<TPrimitiveType *>((*stack)[n - 2]);
  assert(t->primitiveType);
  t->unaryExpression = dynamic_cast<TUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( PrimitiveType [ ] ) UnaryExpression 
void ptCastExpression_LParPrimitiveTypeLSBrRSBrRParUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PrimitiveType);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TCastExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCastExpressionV::LParPrimitiveTypeLSBrRSBrRParUnaryExpression;
  t->oneNt = false;
  t->primitiveType = dynamic_cast<TPrimitiveType *>((*stack)[n - 2]);
  assert(t->primitiveType);
  t->unaryExpression = dynamic_cast<TUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( Expression ) UnaryExpressionNotPlusMinus 
void ptCastExpression_LParExpressionRParUnaryExpressionNotPlusMinus(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpressionNotPlusMinus);
  auto t = new TCastExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCastExpressionV::LParExpressionRParUnaryExpressionNotPlusMinus;
  t->oneNt = false;
  t->expression = dynamic_cast<TExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->unaryExpressionNotPlusMinus = dynamic_cast<TUnaryExpressionNotPlusMinus *>((*stack)[n - 1]);
  assert(t->unaryExpressionNotPlusMinus);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( Name [ ] ) UnaryExpressionNotPlusMinus 
void ptCastExpression_LParNameLSBrRSBrRParUnaryExpressionNotPlusMinus(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Name);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpressionNotPlusMinus);
  auto t = new TCastExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCastExpressionV::LParNameLSBrRSBrRParUnaryExpressionNotPlusMinus;
  t->oneNt = false;
  t->name = dynamic_cast<TName *>((*stack)[n - 2]);
  assert(t->name);
  t->unaryExpressionNotPlusMinus = dynamic_cast<TUnaryExpressionNotPlusMinus *>((*stack)[n - 1]);
  assert(t->unaryExpressionNotPlusMinus);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> UnaryExpression 
void ptMultiplicativeExpression_UnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TMultiplicativeExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TMultiplicativeExpressionV::UnaryExpression;
  t->oneNt = true;
  t->unaryExpression = dynamic_cast<TUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> MultiplicativeExpression * UnaryExpression 
void ptMultiplicativeExpression_MultiplicativeExpressionStarUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::MultiplicativeExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TMultiplicativeExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMultiplicativeExpressionV::MultiplicativeExpressionStarUnaryExpression;
  t->oneNt = false;
  t->multiplicativeExpression = dynamic_cast<TMultiplicativeExpression *>((*stack)[n - 2]);
  assert(t->multiplicativeExpression);
  t->unaryExpression = dynamic_cast<TUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> MultiplicativeExpression / UnaryExpression 
void ptMultiplicativeExpression_MultiplicativeExpressionRSlashUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::MultiplicativeExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TMultiplicativeExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMultiplicativeExpressionV::MultiplicativeExpressionRSlashUnaryExpression;
  t->oneNt = false;
  t->multiplicativeExpression = dynamic_cast<TMultiplicativeExpression *>((*stack)[n - 2]);
  assert(t->multiplicativeExpression);
  t->unaryExpression = dynamic_cast<TUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> MultiplicativeExpression % UnaryExpression 
void ptMultiplicativeExpression_MultiplicativeExpressionPercUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::MultiplicativeExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TMultiplicativeExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMultiplicativeExpressionV::MultiplicativeExpressionPercUnaryExpression;
  t->oneNt = false;
  t->multiplicativeExpression = dynamic_cast<TMultiplicativeExpression *>((*stack)[n - 2]);
  assert(t->multiplicativeExpression);
  t->unaryExpression = dynamic_cast<TUnaryExpression *>((*stack)[n - 1]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// AdditiveExpression -> MultiplicativeExpression 
void ptAdditiveExpression_MultiplicativeExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MultiplicativeExpression);
  auto t = new TAdditiveExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TAdditiveExpressionV::MultiplicativeExpression;
  t->oneNt = true;
  t->multiplicativeExpression = dynamic_cast<TMultiplicativeExpression *>((*stack)[n - 1]);
  assert(t->multiplicativeExpression);
  stack->pop_back();
  stack->push_back(t);
}

// AdditiveExpression -> AdditiveExpression + MultiplicativeExpression 
void ptAdditiveExpression_AdditiveExpressionPlusMultiplicativeExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::AdditiveExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::MultiplicativeExpression);
  auto t = new TAdditiveExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TAdditiveExpressionV::AdditiveExpressionPlusMultiplicativeExpression;
  t->oneNt = false;
  t->additiveExpression = dynamic_cast<TAdditiveExpression *>((*stack)[n - 2]);
  assert(t->additiveExpression);
  t->multiplicativeExpression = dynamic_cast<TMultiplicativeExpression *>((*stack)[n - 1]);
  assert(t->multiplicativeExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// AdditiveExpression -> AdditiveExpression - MultiplicativeExpression 
void ptAdditiveExpression_AdditiveExpressionMinusMultiplicativeExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::AdditiveExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::MultiplicativeExpression);
  auto t = new TAdditiveExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TAdditiveExpressionV::AdditiveExpressionMinusMultiplicativeExpression;
  t->oneNt = false;
  t->additiveExpression = dynamic_cast<TAdditiveExpression *>((*stack)[n - 2]);
  assert(t->additiveExpression);
  t->multiplicativeExpression = dynamic_cast<TMultiplicativeExpression *>((*stack)[n - 1]);
  assert(t->multiplicativeExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> AdditiveExpression 
void ptRelationalExpression_AdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TRelationalExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TRelationalExpressionV::AdditiveExpression;
  t->oneNt = true;
  t->additiveExpression = dynamic_cast<TAdditiveExpression *>((*stack)[n - 1]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression < AdditiveExpression 
void ptRelationalExpression_RelationalExpressionLeAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TRelationalExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TRelationalExpressionV::RelationalExpressionLeAdditiveExpression;
  t->oneNt = false;
  t->relationalExpression = dynamic_cast<TRelationalExpression *>((*stack)[n - 2]);
  assert(t->relationalExpression);
  t->additiveExpression = dynamic_cast<TAdditiveExpression *>((*stack)[n - 1]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression > AdditiveExpression 
void ptRelationalExpression_RelationalExpressionGrAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TRelationalExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TRelationalExpressionV::RelationalExpressionGrAdditiveExpression;
  t->oneNt = false;
  t->relationalExpression = dynamic_cast<TRelationalExpression *>((*stack)[n - 2]);
  assert(t->relationalExpression);
  t->additiveExpression = dynamic_cast<TAdditiveExpression *>((*stack)[n - 1]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression <= AdditiveExpression 
void ptRelationalExpression_RelationalExpressionLeEqAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TRelationalExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TRelationalExpressionV::RelationalExpressionLeEqAdditiveExpression;
  t->oneNt = false;
  t->relationalExpression = dynamic_cast<TRelationalExpression *>((*stack)[n - 2]);
  assert(t->relationalExpression);
  t->additiveExpression = dynamic_cast<TAdditiveExpression *>((*stack)[n - 1]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression >= AdditiveExpression 
void ptRelationalExpression_RelationalExpressionGrEqAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TRelationalExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TRelationalExpressionV::RelationalExpressionGrEqAdditiveExpression;
  t->oneNt = false;
  t->relationalExpression = dynamic_cast<TRelationalExpression *>((*stack)[n - 2]);
  assert(t->relationalExpression);
  t->additiveExpression = dynamic_cast<TAdditiveExpression *>((*stack)[n - 1]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression instanceof ReferenceType 
void ptRelationalExpression_RelationalExpressioninstanceofReferenceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::ReferenceType);
  auto t = new TRelationalExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TRelationalExpressionV::RelationalExpressioninstanceofReferenceType;
  t->oneNt = false;
  t->relationalExpression = dynamic_cast<TRelationalExpression *>((*stack)[n - 2]);
  assert(t->relationalExpression);
  t->referenceType = dynamic_cast<TReferenceType *>((*stack)[n - 1]);
  assert(t->referenceType);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// EqualityExpression -> RelationalExpression 
void ptEqualityExpression_RelationalExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  auto t = new TEqualityExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TEqualityExpressionV::RelationalExpression;
  t->oneNt = true;
  t->relationalExpression = dynamic_cast<TRelationalExpression *>((*stack)[n - 1]);
  assert(t->relationalExpression);
  stack->pop_back();
  stack->push_back(t);
}

// EqualityExpression -> EqualityExpression == RelationalExpression 
void ptEqualityExpression_EqualityExpressionEqEqRelationalExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::EqualityExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  auto t = new TEqualityExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TEqualityExpressionV::EqualityExpressionEqEqRelationalExpression;
  t->oneNt = false;
  t->equalityExpression = dynamic_cast<TEqualityExpression *>((*stack)[n - 2]);
  assert(t->equalityExpression);
  t->relationalExpression = dynamic_cast<TRelationalExpression *>((*stack)[n - 1]);
  assert(t->relationalExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// EqualityExpression -> EqualityExpression != RelationalExpression 
void ptEqualityExpression_EqualityExpressionBangEqRelationalExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::EqualityExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  auto t = new TEqualityExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TEqualityExpressionV::EqualityExpressionBangEqRelationalExpression;
  t->oneNt = false;
  t->equalityExpression = dynamic_cast<TEqualityExpression *>((*stack)[n - 2]);
  assert(t->equalityExpression);
  t->relationalExpression = dynamic_cast<TRelationalExpression *>((*stack)[n - 1]);
  assert(t->relationalExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// AndExpression -> EqualityExpression 
void ptAndExpression_EqualityExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::EqualityExpression);
  auto t = new TAndExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TAndExpressionV::EqualityExpression;
  t->oneNt = true;
  t->equalityExpression = dynamic_cast<TEqualityExpression *>((*stack)[n - 1]);
  assert(t->equalityExpression);
  stack->pop_back();
  stack->push_back(t);
}

// AndExpression -> AndExpression & EqualityExpression 
void ptAndExpression_AndExpressionAmpEqualityExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::AndExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::EqualityExpression);
  auto t = new TAndExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TAndExpressionV::AndExpressionAmpEqualityExpression;
  t->oneNt = false;
  t->andExpression = dynamic_cast<TAndExpression *>((*stack)[n - 2]);
  assert(t->andExpression);
  t->equalityExpression = dynamic_cast<TEqualityExpression *>((*stack)[n - 1]);
  assert(t->equalityExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InclusiveOrExpression -> AndExpression 
void ptInclusiveOrExpression_AndExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AndExpression);
  auto t = new TInclusiveOrExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TInclusiveOrExpressionV::AndExpression;
  t->oneNt = true;
  t->andExpression = dynamic_cast<TAndExpression *>((*stack)[n - 1]);
  assert(t->andExpression);
  stack->pop_back();
  stack->push_back(t);
}

// InclusiveOrExpression -> InclusiveOrExpression | AndExpression 
void ptInclusiveOrExpression_InclusiveOrExpressionOrAndExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::InclusiveOrExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AndExpression);
  auto t = new TInclusiveOrExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TInclusiveOrExpressionV::InclusiveOrExpressionOrAndExpression;
  t->oneNt = false;
  t->inclusiveOrExpression = dynamic_cast<TInclusiveOrExpression *>((*stack)[n - 2]);
  assert(t->inclusiveOrExpression);
  t->andExpression = dynamic_cast<TAndExpression *>((*stack)[n - 1]);
  assert(t->andExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ConditionalAndExpression -> InclusiveOrExpression 
void ptConditionalAndExpression_InclusiveOrExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InclusiveOrExpression);
  auto t = new TConditionalAndExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TConditionalAndExpressionV::InclusiveOrExpression;
  t->oneNt = true;
  t->inclusiveOrExpression = dynamic_cast<TInclusiveOrExpression *>((*stack)[n - 1]);
  assert(t->inclusiveOrExpression);
  stack->pop_back();
  stack->push_back(t);
}

// ConditionalAndExpression -> ConditionalAndExpression && EqualityExpression 
void ptConditionalAndExpression_ConditionalAndExpressionAmpAmpEqualityExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ConditionalAndExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::EqualityExpression);
  auto t = new TConditionalAndExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TConditionalAndExpressionV::ConditionalAndExpressionAmpAmpEqualityExpression;
  t->oneNt = false;
  t->conditionalAndExpression = dynamic_cast<TConditionalAndExpression *>((*stack)[n - 2]);
  assert(t->conditionalAndExpression);
  t->equalityExpression = dynamic_cast<TEqualityExpression *>((*stack)[n - 1]);
  assert(t->equalityExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ConditionalOrExpression -> ConditionalAndExpression 
void ptConditionalOrExpression_ConditionalAndExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ConditionalAndExpression);
  auto t = new TConditionalOrExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TConditionalOrExpressionV::ConditionalAndExpression;
  t->oneNt = true;
  t->conditionalAndExpression = dynamic_cast<TConditionalAndExpression *>((*stack)[n - 1]);
  assert(t->conditionalAndExpression);
  stack->pop_back();
  stack->push_back(t);
}

// ConditionalOrExpression -> ConditionalOrExpression || ConditionalAndExpression 
void ptConditionalOrExpression_ConditionalOrExpressionOrOrConditionalAndExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ConditionalOrExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::ConditionalAndExpression);
  auto t = new TConditionalOrExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TConditionalOrExpressionV::ConditionalOrExpressionOrOrConditionalAndExpression;
  t->oneNt = false;
  t->conditionalOrExpression = dynamic_cast<TConditionalOrExpression *>((*stack)[n - 2]);
  assert(t->conditionalOrExpression);
  t->conditionalAndExpression = dynamic_cast<TConditionalAndExpression *>((*stack)[n - 1]);
  assert(t->conditionalAndExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// AssignmentExpression -> ConditionalOrExpression 
void ptAssignmentExpression_ConditionalOrExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ConditionalOrExpression);
  auto t = new TAssignmentExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TAssignmentExpressionV::ConditionalOrExpression;
  t->oneNt = true;
  t->conditionalOrExpression = dynamic_cast<TConditionalOrExpression *>((*stack)[n - 1]);
  assert(t->conditionalOrExpression);
  stack->pop_back();
  stack->push_back(t);
}

// AssignmentExpression -> Assignment 
void ptAssignmentExpression_Assignment(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Assignment);
  auto t = new TAssignmentExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TAssignmentExpressionV::Assignment;
  t->oneNt = true;
  t->assignment = dynamic_cast<TAssignment *>((*stack)[n - 1]);
  assert(t->assignment);
  stack->pop_back();
  stack->push_back(t);
}

// Assignment -> LeftHandSide = AssignmentExpression 
void ptAssignment_LeftHandSideEqAssignmentExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::LeftHandSide);
  assert((*stack)[n - 1]->type == NonTerminalType::AssignmentExpression);
  auto t = new TAssignment;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TAssignmentV::LeftHandSideEqAssignmentExpression;
  t->oneNt = false;
  t->leftHandSide = dynamic_cast<TLeftHandSide *>((*stack)[n - 2]);
  assert(t->leftHandSide);
  t->assignmentExpression = dynamic_cast<TAssignmentExpression *>((*stack)[n - 1]);
  assert(t->assignmentExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// LeftHandSide -> Name 
void ptLeftHandSide_Name(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TLeftHandSide;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLeftHandSideV::Name;
  t->oneNt = true;
  t->name = dynamic_cast<TName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// LeftHandSide -> FieldAccess 
void ptLeftHandSide_FieldAccess(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FieldAccess);
  auto t = new TLeftHandSide;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLeftHandSideV::FieldAccess;
  t->oneNt = true;
  t->fieldAccess = dynamic_cast<TFieldAccess *>((*stack)[n - 1]);
  assert(t->fieldAccess);
  stack->pop_back();
  stack->push_back(t);
}

// LeftHandSide -> ArrayAccess 
void ptLeftHandSide_ArrayAccess(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayAccess);
  auto t = new TLeftHandSide;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLeftHandSideV::ArrayAccess;
  t->oneNt = true;
  t->arrayAccess = dynamic_cast<TArrayAccess *>((*stack)[n - 1]);
  assert(t->arrayAccess);
  stack->pop_back();
  stack->push_back(t);
}

// Expression -> AssignmentExpression 
void ptExpression_AssignmentExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AssignmentExpression);
  auto t = new TExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TExpressionV::AssignmentExpression;
  t->oneNt = true;
  t->assignmentExpression = dynamic_cast<TAssignmentExpression *>((*stack)[n - 1]);
  assert(t->assignmentExpression);
  stack->pop_back();
  stack->push_back(t);
}

void ptDispatcher(vector<Tree *> *stack, int ruleID) {
  static const ptFunc table[] = {
    ptGoal_BOFCompilationUnitEof, 
    ptLiteral_IntegerLiteral, 
    ptLiteral_BooleanLiteral, 
    ptLiteral_CharacterLiteral, 
    ptLiteral_StringLiteral, 
    ptLiteral_NullLiteral, 
    ptType_PrimitiveType, 
    ptType_ReferenceType, 
    ptPrimitiveType_boolean, 
    ptPrimitiveType_byte, 
    ptPrimitiveType_Short, 
    ptPrimitiveType_Int, 
    ptPrimitiveType_Char, 
    ptReferenceType_ClassOrInterfaceType, 
    ptReferenceType_ArrayType, 
    ptClassOrInterfaceType_Name, 
    ptClassType_ClassOrInterfaceType, 
    ptInterfaceType_ClassOrInterfaceType, 
    ptArrayType_PrimitiveTypeLSBrRSBr, 
    ptArrayType_NameLSBrRSBr, 
    ptName_Identifier, 
    ptName_NameDotIdentifier, 
    ptCompilationUnit_, 
    ptCompilationUnit_PackageDeclaration, 
    ptCompilationUnit_ImportDeclarations, 
    ptCompilationUnit_PackageDeclarationImportDeclarations, 
    ptCompilationUnit_TypeDeclaration, 
    ptCompilationUnit_PackageDeclarationTypeDeclaration, 
    ptCompilationUnit_ImportDeclarationsTypeDeclaration, 
    ptCompilationUnit_PackageDeclarationImportDeclarationsTypeDeclaration, 
    ptImportDeclarations_ImportDeclaration, 
    ptImportDeclarations_ImportDeclarationsImportDeclaration, 
    ptPackageDeclaration_packageNameSCol, 
    ptImportDeclaration_SingleTypeImportDeclaration, 
    ptImportDeclaration_TypeImportOnDemandDeclaration, 
    ptSingleTypeImportDeclaration_importNameSCol, 
    ptTypeImportOnDemandDeclaration_importNameDotStarSCol, 
    ptTypeDeclaration_ClassDeclaration, 
    ptTypeDeclaration_InterfaceDeclaration, 
    ptTypeDeclaration_SCol, 
    ptModifiers_Modifier, 
    ptModifiers_ModifiersModifier, 
    ptModifier_Public, 
    ptModifier_Protected, 
    ptModifier_Static, 
    ptModifier_abstract, 
    ptModifier_final, 
    ptModifier_native, 
    ptClassDeclaration_ModifiersClassIdentifierClassBody, 
    ptClassDeclaration_ModifiersClassIdentifierextendsClassTypeClassBody, 
    ptClassDeclaration_ModifiersClassIdentifierimplementsInterfaceTypeListClassBody, 
    ptClassDeclaration_ModifiersClassIdentifierextendsClassTypeimplementsInterfaceTypeListClassBody, 
    ptInterfaceTypeList_InterfaceType, 
    ptInterfaceTypeList_InterfaceTypeListComInterfaceType, 
    ptClassBody_LCBrRCBr, 
    ptClassBody_LCBrClassMemberDeclarationsRCBr, 
    ptClassMemberDeclarations_ClassMemberDeclaration, 
    ptClassMemberDeclarations_ClassMemberDeclarationsClassMemberDeclaration, 
    ptClassMemberDeclaration_FieldDeclaration, 
    ptClassMemberDeclaration_MethodDeclaration, 
    ptClassMemberDeclaration_ConstructorDeclaration, 
    ptFieldDeclaration_ModifiersTypeVariableDeclaratorSCol, 
    ptVariableDeclarator_Identifier, 
    ptVariableDeclarator_IdentifierEqExpression, 
    ptMethodDeclaration_MethodHeaderMethodBody, 
    ptMethodHeader_TypeMethodDeclarator, 
    ptMethodHeader_ModifiersTypeMethodDeclarator, 
    ptMethodHeader_VoidMethodDeclarator, 
    ptMethodHeader_ModifiersVoidMethodDeclarator, 
    ptMethodDeclarator_IdentifierLParRPar, 
    ptMethodDeclarator_IdentifierLParFormalParameterListRPar, 
    ptFormalParameterList_FormalParameter, 
    ptFormalParameterList_FormalParameterListComFormalParameter, 
    ptFormalParameter_TypeIdentifier, 
    ptMethodBody_Block, 
    ptMethodBody_AbstractMethodBody, 
    ptAbstractMethodBody_SCol, 
    ptConstructorDeclaration_ModifiersConstructorDeclaratorBlock, 
    ptConstructorDeclarator_IdentifierLParRPar, 
    ptConstructorDeclarator_IdentifierLParFormalParameterListRPar, 
    ptInterfaceDeclaration_interfaceIdentifierInterfaceBody, 
    ptInterfaceDeclaration_ModifiersinterfaceIdentifierInterfaceBody, 
    ptInterfaceDeclaration_interfaceIdentifierExtendsInterfacesInterfaceBody, 
    ptInterfaceDeclaration_ModifiersinterfaceIdentifierExtendsInterfacesInterfaceBody, 
    ptExtendsInterfaces_extendsInterfaceType, 
    ptExtendsInterfaces_ExtendsInterfacesComInterfaceType, 
    ptInterfaceBody_LCBrRCBr, 
    ptInterfaceBody_LCBrInterfaceMemberDeclarationsRCBr, 
    ptInterfaceMemberDeclarations_InterfaceMemberDeclaration, 
    ptInterfaceMemberDeclarations_InterfaceMemberDeclarationsInterfaceMemberDeclaration, 
    ptInterfaceMemberDeclaration_AbstractMethodDeclaration, 
    ptAbstractMethodDeclaration_MethodHeaderSCol, 
    ptBlock_LCBrRCBr, 
    ptBlock_LCBrBlockStatementsRCBr, 
    ptBlockStatements_BlockStatement, 
    ptBlockStatements_BlockStatementsBlockStatement, 
    ptBlockStatement_LocalVariableDeclarationStatement, 
    ptBlockStatement_Statement, 
    ptLocalVariableDeclarationStatement_LocalVariableDeclarationSCol, 
    ptLocalVariableDeclaration_TypeVariableDeclarator, 
    ptStatement_StatementWithoutTrailingSubstatement, 
    ptStatement_IfThenStatement, 
    ptStatement_IfThenElseStatement, 
    ptStatement_WhileStatement, 
    ptStatement_ForStatement, 
    ptStatementNoShortIf_StatementWithoutTrailingSubstatement, 
    ptStatementNoShortIf_IfThenElseStatementNoShortIf, 
    ptStatementNoShortIf_WhileStatementNoShortIf, 
    ptStatementNoShortIf_ForStatementNoShortIf, 
    ptStatementWithoutTrailingSubstatement_Block, 
    ptStatementWithoutTrailingSubstatement_ExpressionStatement, 
    ptStatementWithoutTrailingSubstatement_ReturnStatement, 
    ptExpressionStatement_SCol, 
    ptExpressionStatement_StatementExpressionSCol, 
    ptStatementExpression_Assignment, 
    ptStatementExpression_MethodInvocation, 
    ptStatementExpression_ClassInstanceCreationExpression, 
    ptIfThenStatement_IfLParExpressionRParStatement, 
    ptIfThenElseStatement_IfLParExpressionRParStatementNoShortIfElseStatement, 
    ptIfThenElseStatementNoShortIf_IfLParExpressionRParStatementNoShortIfElseStatementNoShortIf, 
    ptWhileStatement_WhileLParExpressionRParStatement, 
    ptWhileStatementNoShortIf_WhileLParExpressionRParStatementNoShortIf, 
    ptForStatement_ForLParForInitSColRParStatement, 
    ptForStatement_ForLParForInitExpressionSColRParStatement, 
    ptForStatement_ForLParForInitSColForUpdateRParStatement, 
    ptForStatement_ForLParForInitExpressionSColForUpdateRParStatement, 
    ptForStatementNoShortIf_ForLParForInitSColRParStatementNoShortIf, 
    ptForStatementNoShortIf_ForLParForInitExpressionSColRParStatementNoShortIf, 
    ptForStatementNoShortIf_ForLParForInitSColForUpdateRParStatementNoShortIf, 
    ptForStatementNoShortIf_ForLParForInitExpressionSColForUpdateRParStatementNoShortIf, 
    ptForInit_ExpressionStatement, 
    ptForInit_LocalVariableDeclarationStatement, 
    ptForUpdate_StatementExpression, 
    ptReturnStatement_ReturnSCol, 
    ptReturnStatement_ReturnExpressionSCol, 
    ptPrimary_PrimaryNoNewArray, 
    ptPrimary_ArrayCreationExpression, 
    ptPrimaryNoNewArray_Literal, 
    ptPrimaryNoNewArray_This2, 
    ptPrimaryNoNewArray_ParenthesizedExpression, 
    ptPrimaryNoNewArray_ClassInstanceCreationExpression, 
    ptPrimaryNoNewArray_FieldAccess, 
    ptPrimaryNoNewArray_MethodInvocation, 
    ptPrimaryNoNewArray_ArrayAccess, 
    ptThis2_This2, 
    ptParenthesizedExpression_LParExpressionRPar, 
    ptClassInstanceCreationExpression_NewClassTypeLParRPar, 
    ptClassInstanceCreationExpression_NewClassTypeLParArgumentListRPar, 
    ptArgumentList_Expression, 
    ptArgumentList_ArgumentListComExpression, 
    ptArrayCreationExpression_NewPrimitiveTypeLSBrExpressionRSBr, 
    ptArrayCreationExpression_NewClassOrInterfaceTypeLSBrExpressionRSBr, 
    ptFieldAccess_PrimaryDotIdentifier, 
    ptMethodInvocation_NameLParRPar, 
    ptMethodInvocation_NameLParArgumentListRPar, 
    ptMethodInvocation_PrimaryDotIdentifierLParRPar, 
    ptMethodInvocation_PrimaryDotIdentifierLParArgumentListRPar, 
    ptArrayAccess_NameLSBrExpressionRSBr, 
    ptArrayAccess_PrimaryNoNewArrayLSBrExpressionRSBr, 
    ptUnaryExpression_MinusUnaryExpression, 
    ptUnaryExpression_UnaryExpressionNotPlusMinus, 
    ptUnaryExpressionNotPlusMinus_Primary, 
    ptUnaryExpressionNotPlusMinus_Name, 
    ptUnaryExpressionNotPlusMinus_BangUnaryExpression, 
    ptUnaryExpressionNotPlusMinus_CastExpression, 
    ptCastExpression_LParPrimitiveTypeRParUnaryExpression, 
    ptCastExpression_LParPrimitiveTypeLSBrRSBrRParUnaryExpression, 
    ptCastExpression_LParExpressionRParUnaryExpressionNotPlusMinus, 
    ptCastExpression_LParNameLSBrRSBrRParUnaryExpressionNotPlusMinus, 
    ptMultiplicativeExpression_UnaryExpression, 
    ptMultiplicativeExpression_MultiplicativeExpressionStarUnaryExpression, 
    ptMultiplicativeExpression_MultiplicativeExpressionRSlashUnaryExpression, 
    ptMultiplicativeExpression_MultiplicativeExpressionPercUnaryExpression, 
    ptAdditiveExpression_MultiplicativeExpression, 
    ptAdditiveExpression_AdditiveExpressionPlusMultiplicativeExpression, 
    ptAdditiveExpression_AdditiveExpressionMinusMultiplicativeExpression, 
    ptRelationalExpression_AdditiveExpression, 
    ptRelationalExpression_RelationalExpressionLeAdditiveExpression, 
    ptRelationalExpression_RelationalExpressionGrAdditiveExpression, 
    ptRelationalExpression_RelationalExpressionLeEqAdditiveExpression, 
    ptRelationalExpression_RelationalExpressionGrEqAdditiveExpression, 
    ptRelationalExpression_RelationalExpressioninstanceofReferenceType, 
    ptEqualityExpression_RelationalExpression, 
    ptEqualityExpression_EqualityExpressionEqEqRelationalExpression, 
    ptEqualityExpression_EqualityExpressionBangEqRelationalExpression, 
    ptAndExpression_EqualityExpression, 
    ptAndExpression_AndExpressionAmpEqualityExpression, 
    ptInclusiveOrExpression_AndExpression, 
    ptInclusiveOrExpression_InclusiveOrExpressionOrAndExpression, 
    ptConditionalAndExpression_InclusiveOrExpression, 
    ptConditionalAndExpression_ConditionalAndExpressionAmpAmpEqualityExpression, 
    ptConditionalOrExpression_ConditionalAndExpression, 
    ptConditionalOrExpression_ConditionalOrExpressionOrOrConditionalAndExpression, 
    ptAssignmentExpression_ConditionalOrExpression, 
    ptAssignmentExpression_Assignment, 
    ptAssignment_LeftHandSideEqAssignmentExpression, 
    ptLeftHandSide_Name, 
    ptLeftHandSide_FieldAccess, 
    ptLeftHandSide_ArrayAccess, 
    ptExpression_AssignmentExpression, 
  };
  table[ruleID](stack);
}

} // namespace Parse 
