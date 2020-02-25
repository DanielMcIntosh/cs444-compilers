#include "parseTreeBase.h"
#include "parseTree.h"
#include "parseTreeNode.h"

namespace Parse { 

using namespace std;

// Goal -> BOF CompilationUnit EOF 
static void ptGoal_BOFCompilationUnitEof(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::CompilationUnit);
  auto t = new TGoal;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TGoalV::BOFCompilationUnitEof;
  t->oneNt = false;
  t->compilationUnit = reinterpret_cast<TCompilationUnit *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> IntegerLiteral 
static void ptLiteral_IntegerLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::IntegerLiteral);
  auto t = new TLiteral;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLiteralV::IntegerLiteral;
  t->oneNt = false;
  t->integerLiteral = reinterpret_cast<TIntegerLiteral *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> BooleanLiteral 
static void ptLiteral_BooleanLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::BooleanLiteral);
  auto t = new TLiteral;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLiteralV::BooleanLiteral;
  t->oneNt = false;
  t->booleanLiteral = reinterpret_cast<TBooleanLiteral *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> CharacterLiteral 
static void ptLiteral_CharacterLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::CharacterLiteral);
  auto t = new TLiteral;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLiteralV::CharacterLiteral;
  t->oneNt = false;
  t->characterLiteral = reinterpret_cast<TCharacterLiteral *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> StringLiteral 
static void ptLiteral_StringLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StringLiteral);
  auto t = new TLiteral;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLiteralV::StringLiteral;
  t->oneNt = false;
  t->stringLiteral = reinterpret_cast<TStringLiteral *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> NullLiteral 
static void ptLiteral_NullLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::NullLiteral);
  auto t = new TLiteral;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLiteralV::NullLiteral;
  t->oneNt = false;
  t->nullLiteral = reinterpret_cast<TNullLiteral *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Type -> PrimitiveType 
static void ptType_PrimitiveType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimitiveType);
  auto t = new TType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TTypeV::PrimitiveType;
  t->oneNt = true;
  t->primitiveType = reinterpret_cast<TPrimitiveType *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Type -> ReferenceType 
static void ptType_ReferenceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ReferenceType);
  auto t = new TType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TTypeV::ReferenceType;
  t->oneNt = true;
  t->referenceType = reinterpret_cast<TReferenceType *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// PrimitiveType -> boolean 
static void ptPrimitiveType_boolean(vector<Tree *> *stack) {
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
static void ptPrimitiveType_byte(vector<Tree *> *stack) {
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
static void ptPrimitiveType_Short(vector<Tree *> *stack) {
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
static void ptPrimitiveType_Int(vector<Tree *> *stack) {
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
static void ptPrimitiveType_Char(vector<Tree *> *stack) {
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
static void ptReferenceType_ClassOrInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassOrInterfaceType);
  auto t = new TReferenceType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TReferenceTypeV::ClassOrInterfaceType;
  t->oneNt = true;
  t->classOrInterfaceType = reinterpret_cast<TClassOrInterfaceType *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ReferenceType -> ArrayType 
static void ptReferenceType_ArrayType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayType);
  auto t = new TReferenceType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TReferenceTypeV::ArrayType;
  t->oneNt = true;
  t->arrayType = reinterpret_cast<TArrayType *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ClassOrInterfaceType -> Name 
static void ptClassOrInterfaceType_Name(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TClassOrInterfaceType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassOrInterfaceTypeV::Name;
  t->oneNt = true;
  t->name = reinterpret_cast<TName *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ClassType -> ClassOrInterfaceType 
static void ptClassType_ClassOrInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassOrInterfaceType);
  auto t = new TClassType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassTypeV::ClassOrInterfaceType;
  t->oneNt = true;
  t->classOrInterfaceType = reinterpret_cast<TClassOrInterfaceType *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceType -> ClassOrInterfaceType 
static void ptInterfaceType_ClassOrInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassOrInterfaceType);
  auto t = new TInterfaceType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TInterfaceTypeV::ClassOrInterfaceType;
  t->oneNt = true;
  t->classOrInterfaceType = reinterpret_cast<TClassOrInterfaceType *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ArrayType -> PrimitiveType [ ] 
static void ptArrayType_PrimitiveTypeLSBrRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimitiveType);
  auto t = new TArrayType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TArrayTypeV::PrimitiveTypeLSBrRSBr;
  t->oneNt = false;
  t->primitiveType = reinterpret_cast<TPrimitiveType *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ArrayType -> Name [ ] 
static void ptArrayType_NameLSBrRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TArrayType;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TArrayTypeV::NameLSBrRSBr;
  t->oneNt = false;
  t->name = reinterpret_cast<TName *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Name -> Identifier 
static void ptName_Identifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TName;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TNameV::Identifier;
  t->oneNt = false;
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Name -> Name . Identifier 
static void ptName_NameDotIdentifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Name);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TName;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TNameV::NameDotIdentifier;
  t->oneNt = false;
  t->name = reinterpret_cast<TName *>((*stack)[n - 2]);
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> 
static void ptCompilationUnit_(vector<Tree *> *stack) {
}

// CompilationUnit -> PackageDeclaration 
static void ptCompilationUnit_PackageDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PackageDeclaration);
  auto t = new TCompilationUnit;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TCompilationUnitV::PackageDeclaration;
  t->oneNt = true;
  t->packageDeclaration = reinterpret_cast<TPackageDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> ImportDeclarations 
static void ptCompilationUnit_ImportDeclarations(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclarations);
  auto t = new TCompilationUnit;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TCompilationUnitV::ImportDeclarations;
  t->oneNt = true;
  t->importDeclarations = reinterpret_cast<TImportDeclarations *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> PackageDeclaration ImportDeclarations 
static void ptCompilationUnit_PackageDeclarationImportDeclarations(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PackageDeclaration);
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclarations);
  auto t = new TCompilationUnit;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCompilationUnitV::PackageDeclarationImportDeclarations;
  t->oneNt = false;
  t->packageDeclaration = reinterpret_cast<TPackageDeclaration *>((*stack)[n - 2]);
  t->importDeclarations = reinterpret_cast<TImportDeclarations *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> TypeDeclaration 
static void ptCompilationUnit_TypeDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclaration);
  auto t = new TCompilationUnit;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TCompilationUnitV::TypeDeclaration;
  t->oneNt = true;
  t->typeDeclaration = reinterpret_cast<TTypeDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> PackageDeclaration TypeDeclaration 
static void ptCompilationUnit_PackageDeclarationTypeDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PackageDeclaration);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclaration);
  auto t = new TCompilationUnit;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCompilationUnitV::PackageDeclarationTypeDeclaration;
  t->oneNt = false;
  t->packageDeclaration = reinterpret_cast<TPackageDeclaration *>((*stack)[n - 2]);
  t->typeDeclaration = reinterpret_cast<TTypeDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> ImportDeclarations TypeDeclaration 
static void ptCompilationUnit_ImportDeclarationsTypeDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ImportDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclaration);
  auto t = new TCompilationUnit;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCompilationUnitV::ImportDeclarationsTypeDeclaration;
  t->oneNt = false;
  t->importDeclarations = reinterpret_cast<TImportDeclarations *>((*stack)[n - 2]);
  t->typeDeclaration = reinterpret_cast<TTypeDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> PackageDeclaration ImportDeclarations TypeDeclaration 
static void ptCompilationUnit_PackageDeclarationImportDeclarationsTypeDeclaration(vector<Tree *> *stack) {
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
  t->packageDeclaration = reinterpret_cast<TPackageDeclaration *>((*stack)[n - 3]);
  t->importDeclarations = reinterpret_cast<TImportDeclarations *>((*stack)[n - 2]);
  t->typeDeclaration = reinterpret_cast<TTypeDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ImportDeclarations -> ImportDeclaration 
static void ptImportDeclarations_ImportDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclaration);
  auto t = new TImportDeclarations;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TImportDeclarationsV::ImportDeclaration;
  t->oneNt = true;
  t->importDeclaration = reinterpret_cast<TImportDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ImportDeclarations -> ImportDeclarations ImportDeclaration 
static void ptImportDeclarations_ImportDeclarationsImportDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ImportDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclaration);
  auto t = new TImportDeclarations;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TImportDeclarationsV::ImportDeclarationsImportDeclaration;
  t->oneNt = false;
  t->importDeclarations = reinterpret_cast<TImportDeclarations *>((*stack)[n - 2]);
  t->importDeclaration = reinterpret_cast<TImportDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// PackageDeclaration -> package Name ; 
static void ptPackageDeclaration_packageNameSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TPackageDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPackageDeclarationV::packageNameSCol;
  t->oneNt = false;
  t->name = reinterpret_cast<TName *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ImportDeclaration -> SingleTypeImportDeclaration 
static void ptImportDeclaration_SingleTypeImportDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::SingleTypeImportDeclaration);
  auto t = new TImportDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TImportDeclarationV::SingleTypeImportDeclaration;
  t->oneNt = true;
  t->singleTypeImportDeclaration = reinterpret_cast<TSingleTypeImportDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ImportDeclaration -> TypeImportOnDemandDeclaration 
static void ptImportDeclaration_TypeImportOnDemandDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeImportOnDemandDeclaration);
  auto t = new TImportDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TImportDeclarationV::TypeImportOnDemandDeclaration;
  t->oneNt = true;
  t->typeImportOnDemandDeclaration = reinterpret_cast<TTypeImportOnDemandDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// SingleTypeImportDeclaration -> import Name ; 
static void ptSingleTypeImportDeclaration_importNameSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TSingleTypeImportDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TSingleTypeImportDeclarationV::importNameSCol;
  t->oneNt = false;
  t->name = reinterpret_cast<TName *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// TypeImportOnDemandDeclaration -> import Name . * ; 
static void ptTypeImportOnDemandDeclaration_importNameDotStarSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TTypeImportOnDemandDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TTypeImportOnDemandDeclarationV::importNameDotStarSCol;
  t->oneNt = false;
  t->name = reinterpret_cast<TName *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// TypeDeclaration -> ClassDeclaration 
static void ptTypeDeclaration_ClassDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassDeclaration);
  auto t = new TTypeDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TTypeDeclarationV::ClassDeclaration;
  t->oneNt = true;
  t->classDeclaration = reinterpret_cast<TClassDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// TypeDeclaration -> InterfaceDeclaration 
static void ptTypeDeclaration_InterfaceDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceDeclaration);
  auto t = new TTypeDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TTypeDeclarationV::InterfaceDeclaration;
  t->oneNt = true;
  t->interfaceDeclaration = reinterpret_cast<TInterfaceDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// TypeDeclaration -> ; 
static void ptTypeDeclaration_SCol(vector<Tree *> *stack) {
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
static void ptModifiers_Modifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifier);
  auto t = new TModifiers;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TModifiersV::Modifier;
  t->oneNt = true;
  t->modifier = reinterpret_cast<TModifier *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Modifiers -> Modifiers Modifier 
static void ptModifiers_ModifiersModifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifier);
  auto t = new TModifiers;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TModifiersV::ModifiersModifier;
  t->oneNt = false;
  t->modifiers = reinterpret_cast<TModifiers *>((*stack)[n - 2]);
  t->modifier = reinterpret_cast<TModifier *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// Modifier -> public 
static void ptModifier_Public(vector<Tree *> *stack) {
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
static void ptModifier_Protected(vector<Tree *> *stack) {
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
static void ptModifier_Static(vector<Tree *> *stack) {
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
static void ptModifier_abstract(vector<Tree *> *stack) {
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
static void ptModifier_final(vector<Tree *> *stack) {
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
static void ptModifier_native(vector<Tree *> *stack) {
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
static void ptClassDeclaration_ModifiersClassIdentifierClassBody(vector<Tree *> *stack) {
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
  t->modifiers = reinterpret_cast<TModifiers *>((*stack)[n - 3]);
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 2]);
  t->classBody = reinterpret_cast<TClassBody *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier extends ClassType ClassBody 
static void ptClassDeclaration_ModifiersClassIdentifierextendsClassTypeClassBody(vector<Tree *> *stack) {
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
  t->modifiers = reinterpret_cast<TModifiers *>((*stack)[n - 4]);
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 3]);
  t->classType = reinterpret_cast<TClassType *>((*stack)[n - 2]);
  t->classBody = reinterpret_cast<TClassBody *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier implements InterfaceTypeList ClassBody 
static void ptClassDeclaration_ModifiersClassIdentifierimplementsInterfaceTypeListClassBody(vector<Tree *> *stack) {
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
  t->modifiers = reinterpret_cast<TModifiers *>((*stack)[n - 4]);
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 3]);
  t->interfaceTypeList = reinterpret_cast<TInterfaceTypeList *>((*stack)[n - 2]);
  t->classBody = reinterpret_cast<TClassBody *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier extends ClassType implements InterfaceTypeList ClassBody 
static void ptClassDeclaration_ModifiersClassIdentifierextendsClassTypeimplementsInterfaceTypeListClassBody(vector<Tree *> *stack) {
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
  t->modifiers = reinterpret_cast<TModifiers *>((*stack)[n - 5]);
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 4]);
  t->classType = reinterpret_cast<TClassType *>((*stack)[n - 3]);
  t->interfaceTypeList = reinterpret_cast<TInterfaceTypeList *>((*stack)[n - 2]);
  t->classBody = reinterpret_cast<TClassBody *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceTypeList -> InterfaceType 
static void ptInterfaceTypeList_InterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceType);
  auto t = new TInterfaceTypeList;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TInterfaceTypeListV::InterfaceType;
  t->oneNt = true;
  t->interfaceType = reinterpret_cast<TInterfaceType *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceTypeList -> InterfaceTypeList , InterfaceType 
static void ptInterfaceTypeList_InterfaceTypeListComInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceTypeList);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceType);
  auto t = new TInterfaceTypeList;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TInterfaceTypeListV::InterfaceTypeListComInterfaceType;
  t->oneNt = false;
  t->interfaceTypeList = reinterpret_cast<TInterfaceTypeList *>((*stack)[n - 2]);
  t->interfaceType = reinterpret_cast<TInterfaceType *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassBody -> { } 
static void ptClassBody_LCBrRCBr(vector<Tree *> *stack) {
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
static void ptClassBody_LCBrClassMemberDeclarationsRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassMemberDeclarations);
  auto t = new TClassBody;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassBodyV::LCBrClassMemberDeclarationsRCBr;
  t->oneNt = false;
  t->classMemberDeclarations = reinterpret_cast<TClassMemberDeclarations *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclarations -> ClassMemberDeclaration 
static void ptClassMemberDeclarations_ClassMemberDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassMemberDeclaration);
  auto t = new TClassMemberDeclarations;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassMemberDeclarationsV::ClassMemberDeclaration;
  t->oneNt = true;
  t->classMemberDeclaration = reinterpret_cast<TClassMemberDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclarations -> ClassMemberDeclarations ClassMemberDeclaration 
static void ptClassMemberDeclarations_ClassMemberDeclarationsClassMemberDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassMemberDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassMemberDeclaration);
  auto t = new TClassMemberDeclarations;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TClassMemberDeclarationsV::ClassMemberDeclarationsClassMemberDeclaration;
  t->oneNt = false;
  t->classMemberDeclarations = reinterpret_cast<TClassMemberDeclarations *>((*stack)[n - 2]);
  t->classMemberDeclaration = reinterpret_cast<TClassMemberDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclaration -> FieldDeclaration 
static void ptClassMemberDeclaration_FieldDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FieldDeclaration);
  auto t = new TClassMemberDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassMemberDeclarationV::FieldDeclaration;
  t->oneNt = true;
  t->fieldDeclaration = reinterpret_cast<TFieldDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclaration -> MethodDeclaration 
static void ptClassMemberDeclaration_MethodDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclaration);
  auto t = new TClassMemberDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassMemberDeclarationV::MethodDeclaration;
  t->oneNt = true;
  t->methodDeclaration = reinterpret_cast<TMethodDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclaration -> ConstructorDeclaration 
static void ptClassMemberDeclaration_ConstructorDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ConstructorDeclaration);
  auto t = new TClassMemberDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassMemberDeclarationV::ConstructorDeclaration;
  t->oneNt = true;
  t->constructorDeclaration = reinterpret_cast<TConstructorDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// FieldDeclaration -> Modifiers VariableDeclaration ; 
static void ptFieldDeclaration_ModifiersVariableDeclarationSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableDeclaration);
  auto t = new TFieldDeclaration;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TFieldDeclarationV::ModifiersVariableDeclarationSCol;
  t->oneNt = false;
  t->modifiers = reinterpret_cast<TModifiers *>((*stack)[n - 2]);
  t->variableDeclaration = reinterpret_cast<TVariableDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// VariableDeclarator -> Identifier 
static void ptVariableDeclarator_Identifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TVariableDeclarator;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TVariableDeclaratorV::Identifier;
  t->oneNt = false;
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// VariableDeclarator -> Identifier = Expression 
static void ptVariableDeclarator_IdentifierEqExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TVariableDeclarator;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TVariableDeclaratorV::IdentifierEqExpression;
  t->oneNt = false;
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 2]);
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodDeclaration -> MethodHeader MethodBody 
static void ptMethodDeclaration_MethodHeaderMethodBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::MethodHeader);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodBody);
  auto t = new TMethodDeclaration;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMethodDeclarationV::MethodHeaderMethodBody;
  t->oneNt = false;
  t->methodHeader = reinterpret_cast<TMethodHeader *>((*stack)[n - 2]);
  t->methodBody = reinterpret_cast<TMethodBody *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> Type MethodDeclarator 
static void ptMethodHeader_TypeMethodDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclarator);
  auto t = new TMethodHeader;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMethodHeaderV::TypeMethodDeclarator;
  t->oneNt = false;
  t->type = reinterpret_cast<TType *>((*stack)[n - 2]);
  t->methodDeclarator = reinterpret_cast<TMethodDeclarator *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> Modifiers Type MethodDeclarator 
static void ptMethodHeader_ModifiersTypeMethodDeclarator(vector<Tree *> *stack) {
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
  t->modifiers = reinterpret_cast<TModifiers *>((*stack)[n - 3]);
  t->type = reinterpret_cast<TType *>((*stack)[n - 2]);
  t->methodDeclarator = reinterpret_cast<TMethodDeclarator *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> void MethodDeclarator 
static void ptMethodHeader_VoidMethodDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclarator);
  auto t = new TMethodHeader;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TMethodHeaderV::VoidMethodDeclarator;
  t->oneNt = false;
  t->methodDeclarator = reinterpret_cast<TMethodDeclarator *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> Modifiers void MethodDeclarator 
static void ptMethodHeader_ModifiersVoidMethodDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclarator);
  auto t = new TMethodHeader;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMethodHeaderV::ModifiersVoidMethodDeclarator;
  t->oneNt = false;
  t->modifiers = reinterpret_cast<TModifiers *>((*stack)[n - 2]);
  t->methodDeclarator = reinterpret_cast<TMethodDeclarator *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodDeclarator -> Identifier ( ) 
static void ptMethodDeclarator_IdentifierLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TMethodDeclarator;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TMethodDeclaratorV::IdentifierLParRPar;
  t->oneNt = false;
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// MethodDeclarator -> Identifier ( FormalParameterList ) 
static void ptMethodDeclarator_IdentifierLParFormalParameterListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameterList);
  auto t = new TMethodDeclarator;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMethodDeclaratorV::IdentifierLParFormalParameterListRPar;
  t->oneNt = false;
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 2]);
  t->formalParameterList = reinterpret_cast<TFormalParameterList *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// FormalParameterList -> FormalParameter 
static void ptFormalParameterList_FormalParameter(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameter);
  auto t = new TFormalParameterList;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TFormalParameterListV::FormalParameter;
  t->oneNt = true;
  t->formalParameter = reinterpret_cast<TFormalParameter *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// FormalParameterList -> FormalParameterList , FormalParameter 
static void ptFormalParameterList_FormalParameterListComFormalParameter(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::FormalParameterList);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameter);
  auto t = new TFormalParameterList;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TFormalParameterListV::FormalParameterListComFormalParameter;
  t->oneNt = false;
  t->formalParameterList = reinterpret_cast<TFormalParameterList *>((*stack)[n - 2]);
  t->formalParameter = reinterpret_cast<TFormalParameter *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// FormalParameter -> Type Identifier 
static void ptFormalParameter_TypeIdentifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TFormalParameter;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TFormalParameterV::TypeIdentifier;
  t->oneNt = false;
  t->type = reinterpret_cast<TType *>((*stack)[n - 2]);
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodBody -> Block 
static void ptMethodBody_Block(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Block);
  auto t = new TMethodBody;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TMethodBodyV::Block;
  t->oneNt = true;
  t->block = reinterpret_cast<TBlock *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// MethodBody -> AbstractMethodBody 
static void ptMethodBody_AbstractMethodBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AbstractMethodBody);
  auto t = new TMethodBody;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TMethodBodyV::AbstractMethodBody;
  t->oneNt = true;
  t->abstractMethodBody = reinterpret_cast<TAbstractMethodBody *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// AbstractMethodBody -> ; 
static void ptAbstractMethodBody_SCol(vector<Tree *> *stack) {
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
static void ptConstructorDeclaration_ModifiersConstructorDeclaratorBlock(vector<Tree *> *stack) {
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
  t->modifiers = reinterpret_cast<TModifiers *>((*stack)[n - 3]);
  t->constructorDeclarator = reinterpret_cast<TConstructorDeclarator *>((*stack)[n - 2]);
  t->block = reinterpret_cast<TBlock *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ConstructorDeclarator -> Identifier ( ) 
static void ptConstructorDeclarator_IdentifierLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TConstructorDeclarator;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TConstructorDeclaratorV::IdentifierLParRPar;
  t->oneNt = false;
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ConstructorDeclarator -> Identifier ( FormalParameterList ) 
static void ptConstructorDeclarator_IdentifierLParFormalParameterListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameterList);
  auto t = new TConstructorDeclarator;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TConstructorDeclaratorV::IdentifierLParFormalParameterListRPar;
  t->oneNt = false;
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 2]);
  t->formalParameterList = reinterpret_cast<TFormalParameterList *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> interface Identifier InterfaceBody 
static void ptInterfaceDeclaration_interfaceIdentifierInterfaceBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Identifier);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceBody);
  auto t = new TInterfaceDeclaration;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TInterfaceDeclarationV::interfaceIdentifierInterfaceBody;
  t->oneNt = false;
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 2]);
  t->interfaceBody = reinterpret_cast<TInterfaceBody *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> Modifiers interface Identifier InterfaceBody 
static void ptInterfaceDeclaration_ModifiersinterfaceIdentifierInterfaceBody(vector<Tree *> *stack) {
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
  t->modifiers = reinterpret_cast<TModifiers *>((*stack)[n - 3]);
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 2]);
  t->interfaceBody = reinterpret_cast<TInterfaceBody *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> interface Identifier ExtendsInterfaces InterfaceBody 
static void ptInterfaceDeclaration_interfaceIdentifierExtendsInterfacesInterfaceBody(vector<Tree *> *stack) {
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
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 3]);
  t->extendsInterfaces = reinterpret_cast<TExtendsInterfaces *>((*stack)[n - 2]);
  t->interfaceBody = reinterpret_cast<TInterfaceBody *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> Modifiers interface Identifier ExtendsInterfaces InterfaceBody 
static void ptInterfaceDeclaration_ModifiersinterfaceIdentifierExtendsInterfacesInterfaceBody(vector<Tree *> *stack) {
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
  t->modifiers = reinterpret_cast<TModifiers *>((*stack)[n - 4]);
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 3]);
  t->extendsInterfaces = reinterpret_cast<TExtendsInterfaces *>((*stack)[n - 2]);
  t->interfaceBody = reinterpret_cast<TInterfaceBody *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ExtendsInterfaces -> extends InterfaceType 
static void ptExtendsInterfaces_extendsInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceType);
  auto t = new TExtendsInterfaces;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TExtendsInterfacesV::extendsInterfaceType;
  t->oneNt = false;
  t->interfaceType = reinterpret_cast<TInterfaceType *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ExtendsInterfaces -> ExtendsInterfaces , InterfaceType 
static void ptExtendsInterfaces_ExtendsInterfacesComInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ExtendsInterfaces);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceType);
  auto t = new TExtendsInterfaces;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TExtendsInterfacesV::ExtendsInterfacesComInterfaceType;
  t->oneNt = false;
  t->extendsInterfaces = reinterpret_cast<TExtendsInterfaces *>((*stack)[n - 2]);
  t->interfaceType = reinterpret_cast<TInterfaceType *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceBody -> { } 
static void ptInterfaceBody_LCBrRCBr(vector<Tree *> *stack) {
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
static void ptInterfaceBody_LCBrInterfaceMemberDeclarationsRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceMemberDeclarations);
  auto t = new TInterfaceBody;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TInterfaceBodyV::LCBrInterfaceMemberDeclarationsRCBr;
  t->oneNt = false;
  t->interfaceMemberDeclarations = reinterpret_cast<TInterfaceMemberDeclarations *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceMemberDeclarations -> InterfaceMemberDeclaration 
static void ptInterfaceMemberDeclarations_InterfaceMemberDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceMemberDeclaration);
  auto t = new TInterfaceMemberDeclarations;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TInterfaceMemberDeclarationsV::InterfaceMemberDeclaration;
  t->oneNt = true;
  t->interfaceMemberDeclaration = reinterpret_cast<TInterfaceMemberDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceMemberDeclarations -> InterfaceMemberDeclarations InterfaceMemberDeclaration 
static void ptInterfaceMemberDeclarations_InterfaceMemberDeclarationsInterfaceMemberDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceMemberDeclarations);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceMemberDeclaration);
  auto t = new TInterfaceMemberDeclarations;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TInterfaceMemberDeclarationsV::InterfaceMemberDeclarationsInterfaceMemberDeclaration;
  t->oneNt = false;
  t->interfaceMemberDeclarations = reinterpret_cast<TInterfaceMemberDeclarations *>((*stack)[n - 2]);
  t->interfaceMemberDeclaration = reinterpret_cast<TInterfaceMemberDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceMemberDeclaration -> AbstractMethodDeclaration 
static void ptInterfaceMemberDeclaration_AbstractMethodDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AbstractMethodDeclaration);
  auto t = new TInterfaceMemberDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TInterfaceMemberDeclarationV::AbstractMethodDeclaration;
  t->oneNt = true;
  t->abstractMethodDeclaration = reinterpret_cast<TAbstractMethodDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// AbstractMethodDeclaration -> MethodHeader ; 
static void ptAbstractMethodDeclaration_MethodHeaderSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodHeader);
  auto t = new TAbstractMethodDeclaration;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TAbstractMethodDeclarationV::MethodHeaderSCol;
  t->oneNt = false;
  t->methodHeader = reinterpret_cast<TMethodHeader *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Block -> { } 
static void ptBlock_LCBrRCBr(vector<Tree *> *stack) {
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
static void ptBlock_LCBrBlockStatementsRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::BlockStatements);
  auto t = new TBlock;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TBlockV::LCBrBlockStatementsRCBr;
  t->oneNt = false;
  t->blockStatements = reinterpret_cast<TBlockStatements *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// BlockStatements -> BlockStatement 
static void ptBlockStatements_BlockStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::BlockStatement);
  auto t = new TBlockStatements;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TBlockStatementsV::BlockStatement;
  t->oneNt = true;
  t->blockStatement = reinterpret_cast<TBlockStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// BlockStatements -> BlockStatements BlockStatement 
static void ptBlockStatements_BlockStatementsBlockStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::BlockStatements);
  assert((*stack)[n - 1]->type == NonTerminalType::BlockStatement);
  auto t = new TBlockStatements;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TBlockStatementsV::BlockStatementsBlockStatement;
  t->oneNt = false;
  t->blockStatements = reinterpret_cast<TBlockStatements *>((*stack)[n - 2]);
  t->blockStatement = reinterpret_cast<TBlockStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// BlockStatement -> LocalVariableDeclarationStatement 
static void ptBlockStatement_LocalVariableDeclarationStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::LocalVariableDeclarationStatement);
  auto t = new TBlockStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TBlockStatementV::LocalVariableDeclarationStatement;
  t->oneNt = true;
  t->localVariableDeclarationStatement = reinterpret_cast<TLocalVariableDeclarationStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// BlockStatement -> Statement 
static void ptBlockStatement_Statement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TBlockStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TBlockStatementV::Statement;
  t->oneNt = true;
  t->statement = reinterpret_cast<TStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// LocalVariableDeclarationStatement -> VariableDeclaration ; 
static void ptLocalVariableDeclarationStatement_VariableDeclarationSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableDeclaration);
  auto t = new TLocalVariableDeclarationStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLocalVariableDeclarationStatementV::VariableDeclarationSCol;
  t->oneNt = false;
  t->variableDeclaration = reinterpret_cast<TVariableDeclaration *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// VariableDeclaration -> Type VariableDeclarator 
static void ptVariableDeclaration_TypeVariableDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableDeclarator);
  auto t = new TVariableDeclaration;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TVariableDeclarationV::TypeVariableDeclarator;
  t->oneNt = false;
  t->type = reinterpret_cast<TType *>((*stack)[n - 2]);
  t->variableDeclarator = reinterpret_cast<TVariableDeclarator *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> StatementWithoutTrailingSubstatement 
static void ptStatement_StatementWithoutTrailingSubstatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementWithoutTrailingSubstatement);
  auto t = new TStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementV::StatementWithoutTrailingSubstatement;
  t->oneNt = true;
  t->statementWithoutTrailingSubstatement = reinterpret_cast<TStatementWithoutTrailingSubstatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> IfThenStatement 
static void ptStatement_IfThenStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::IfThenStatement);
  auto t = new TStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementV::IfThenStatement;
  t->oneNt = true;
  t->ifThenStatement = reinterpret_cast<TIfThenStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> IfThenElseStatement 
static void ptStatement_IfThenElseStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::IfThenElseStatement);
  auto t = new TStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementV::IfThenElseStatement;
  t->oneNt = true;
  t->ifThenElseStatement = reinterpret_cast<TIfThenElseStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> WhileStatement 
static void ptStatement_WhileStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::WhileStatement);
  auto t = new TStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementV::WhileStatement;
  t->oneNt = true;
  t->whileStatement = reinterpret_cast<TWhileStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Statement -> ForStatement 
static void ptStatement_ForStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ForStatement);
  auto t = new TStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementV::ForStatement;
  t->oneNt = true;
  t->forStatement = reinterpret_cast<TForStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// StatementNoShortIf -> StatementWithoutTrailingSubstatement 
static void ptStatementNoShortIf_StatementWithoutTrailingSubstatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementWithoutTrailingSubstatement);
  auto t = new TStatementNoShortIf;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementNoShortIfV::StatementWithoutTrailingSubstatement;
  t->oneNt = true;
  t->statementWithoutTrailingSubstatement = reinterpret_cast<TStatementWithoutTrailingSubstatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// StatementNoShortIf -> IfThenElseStatementNoShortIf 
static void ptStatementNoShortIf_IfThenElseStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::IfThenElseStatementNoShortIf);
  auto t = new TStatementNoShortIf;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementNoShortIfV::IfThenElseStatementNoShortIf;
  t->oneNt = true;
  t->ifThenElseStatementNoShortIf = reinterpret_cast<TIfThenElseStatementNoShortIf *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// StatementNoShortIf -> WhileStatementNoShortIf 
static void ptStatementNoShortIf_WhileStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::WhileStatementNoShortIf);
  auto t = new TStatementNoShortIf;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementNoShortIfV::WhileStatementNoShortIf;
  t->oneNt = true;
  t->whileStatementNoShortIf = reinterpret_cast<TWhileStatementNoShortIf *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// StatementNoShortIf -> ForStatementNoShortIf 
static void ptStatementNoShortIf_ForStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ForStatementNoShortIf);
  auto t = new TStatementNoShortIf;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementNoShortIfV::ForStatementNoShortIf;
  t->oneNt = true;
  t->forStatementNoShortIf = reinterpret_cast<TForStatementNoShortIf *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// StatementWithoutTrailingSubstatement -> Block 
static void ptStatementWithoutTrailingSubstatement_Block(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Block);
  auto t = new TStatementWithoutTrailingSubstatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementWithoutTrailingSubstatementV::Block;
  t->oneNt = true;
  t->block = reinterpret_cast<TBlock *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// StatementWithoutTrailingSubstatement -> ExpressionStatement 
static void ptStatementWithoutTrailingSubstatement_ExpressionStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ExpressionStatement);
  auto t = new TStatementWithoutTrailingSubstatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementWithoutTrailingSubstatementV::ExpressionStatement;
  t->oneNt = true;
  t->expressionStatement = reinterpret_cast<TExpressionStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// StatementWithoutTrailingSubstatement -> ReturnStatement 
static void ptStatementWithoutTrailingSubstatement_ReturnStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ReturnStatement);
  auto t = new TStatementWithoutTrailingSubstatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementWithoutTrailingSubstatementV::ReturnStatement;
  t->oneNt = true;
  t->returnStatement = reinterpret_cast<TReturnStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ExpressionStatement -> ; 
static void ptExpressionStatement_SCol(vector<Tree *> *stack) {
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
static void ptExpressionStatement_StatementExpressionSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementExpression);
  auto t = new TExpressionStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TExpressionStatementV::StatementExpressionSCol;
  t->oneNt = false;
  t->statementExpression = reinterpret_cast<TStatementExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// StatementExpression -> Assignment 
static void ptStatementExpression_Assignment(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Assignment);
  auto t = new TStatementExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementExpressionV::Assignment;
  t->oneNt = true;
  t->assignment = reinterpret_cast<TAssignment *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// StatementExpression -> MethodInvocation 
static void ptStatementExpression_MethodInvocation(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodInvocation);
  auto t = new TStatementExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementExpressionV::MethodInvocation;
  t->oneNt = true;
  t->methodInvocation = reinterpret_cast<TMethodInvocation *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// StatementExpression -> ClassInstanceCreationExpression 
static void ptStatementExpression_ClassInstanceCreationExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassInstanceCreationExpression);
  auto t = new TStatementExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TStatementExpressionV::ClassInstanceCreationExpression;
  t->oneNt = true;
  t->classInstanceCreationExpression = reinterpret_cast<TClassInstanceCreationExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// IfThenStatement -> if ( Expression ) Statement 
static void ptIfThenStatement_IfLParExpressionRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TIfThenStatement;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TIfThenStatementV::IfLParExpressionRParStatement;
  t->oneNt = false;
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 2]);
  t->statement = reinterpret_cast<TStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// IfThenElseStatement -> if ( Expression ) StatementNoShortIf else Statement 
static void ptIfThenElseStatement_IfLParExpressionRParStatementNoShortIfElseStatement(vector<Tree *> *stack) {
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
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 3]);
  t->statementNoShortIf = reinterpret_cast<TStatementNoShortIf *>((*stack)[n - 2]);
  t->statement = reinterpret_cast<TStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// IfThenElseStatementNoShortIf -> if ( Expression ) StatementNoShortIf else StatementNoShortIf 
static void ptIfThenElseStatementNoShortIf_IfLParExpressionRParStatementNoShortIfElseStatementNoShortIf(vector<Tree *> *stack) {
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
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 3]);
  t->statementNoShortIf = reinterpret_cast<TStatementNoShortIf *>((*stack)[n - 2]);
  t->statementNoShortIf2 = reinterpret_cast<TStatementNoShortIf *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// WhileStatement -> while ( Expression ) Statement 
static void ptWhileStatement_WhileLParExpressionRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TWhileStatement;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TWhileStatementV::WhileLParExpressionRParStatement;
  t->oneNt = false;
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 2]);
  t->statement = reinterpret_cast<TStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// WhileStatementNoShortIf -> while ( Expression ) StatementNoShortIf 
static void ptWhileStatementNoShortIf_WhileLParExpressionRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TWhileStatementNoShortIf;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TWhileStatementNoShortIfV::WhileLParExpressionRParStatementNoShortIf;
  t->oneNt = false;
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 2]);
  t->statementNoShortIf = reinterpret_cast<TStatementNoShortIf *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit ; ) Statement 
static void ptForStatement_ForLParForInitSColRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 1]->type == NonTerminalType::Statement);
  auto t = new TForStatement;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TForStatementV::ForLParForInitSColRParStatement;
  t->oneNt = false;
  t->forInit = reinterpret_cast<TForInit *>((*stack)[n - 2]);
  t->statement = reinterpret_cast<TStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit Expression ; ) Statement 
static void ptForStatement_ForLParForInitExpressionSColRParStatement(vector<Tree *> *stack) {
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
  t->forInit = reinterpret_cast<TForInit *>((*stack)[n - 3]);
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 2]);
  t->statement = reinterpret_cast<TStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit ; ForUpdate ) Statement 
static void ptForStatement_ForLParForInitSColForUpdateRParStatement(vector<Tree *> *stack) {
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
  t->forInit = reinterpret_cast<TForInit *>((*stack)[n - 3]);
  t->forUpdate = reinterpret_cast<TForUpdate *>((*stack)[n - 2]);
  t->statement = reinterpret_cast<TStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit Expression ; ForUpdate ) Statement 
static void ptForStatement_ForLParForInitExpressionSColForUpdateRParStatement(vector<Tree *> *stack) {
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
  t->forInit = reinterpret_cast<TForInit *>((*stack)[n - 4]);
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 3]);
  t->forUpdate = reinterpret_cast<TForUpdate *>((*stack)[n - 2]);
  t->statement = reinterpret_cast<TStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit ; ) StatementNoShortIf 
static void ptForStatementNoShortIf_ForLParForInitSColRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TForStatementNoShortIf;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TForStatementNoShortIfV::ForLParForInitSColRParStatementNoShortIf;
  t->oneNt = false;
  t->forInit = reinterpret_cast<TForInit *>((*stack)[n - 2]);
  t->statementNoShortIf = reinterpret_cast<TStatementNoShortIf *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit Expression ; ) StatementNoShortIf 
static void ptForStatementNoShortIf_ForLParForInitExpressionSColRParStatementNoShortIf(vector<Tree *> *stack) {
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
  t->forInit = reinterpret_cast<TForInit *>((*stack)[n - 3]);
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 2]);
  t->statementNoShortIf = reinterpret_cast<TStatementNoShortIf *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit ; ForUpdate ) StatementNoShortIf 
static void ptForStatementNoShortIf_ForLParForInitSColForUpdateRParStatementNoShortIf(vector<Tree *> *stack) {
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
  t->forInit = reinterpret_cast<TForInit *>((*stack)[n - 3]);
  t->forUpdate = reinterpret_cast<TForUpdate *>((*stack)[n - 2]);
  t->statementNoShortIf = reinterpret_cast<TStatementNoShortIf *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit Expression ; ForUpdate ) StatementNoShortIf 
static void ptForStatementNoShortIf_ForLParForInitExpressionSColForUpdateRParStatementNoShortIf(vector<Tree *> *stack) {
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
  t->forInit = reinterpret_cast<TForInit *>((*stack)[n - 4]);
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 3]);
  t->forUpdate = reinterpret_cast<TForUpdate *>((*stack)[n - 2]);
  t->statementNoShortIf = reinterpret_cast<TStatementNoShortIf *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForInit -> ExpressionStatement 
static void ptForInit_ExpressionStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ExpressionStatement);
  auto t = new TForInit;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TForInitV::ExpressionStatement;
  t->oneNt = true;
  t->expressionStatement = reinterpret_cast<TExpressionStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ForInit -> LocalVariableDeclarationStatement 
static void ptForInit_LocalVariableDeclarationStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::LocalVariableDeclarationStatement);
  auto t = new TForInit;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TForInitV::LocalVariableDeclarationStatement;
  t->oneNt = true;
  t->localVariableDeclarationStatement = reinterpret_cast<TLocalVariableDeclarationStatement *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ForUpdate -> StatementExpression 
static void ptForUpdate_StatementExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementExpression);
  auto t = new TForUpdate;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TForUpdateV::StatementExpression;
  t->oneNt = true;
  t->statementExpression = reinterpret_cast<TStatementExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ReturnStatement -> return ; 
static void ptReturnStatement_ReturnSCol(vector<Tree *> *stack) {
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
static void ptReturnStatement_ReturnExpressionSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TReturnStatement;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TReturnStatementV::ReturnExpressionSCol;
  t->oneNt = false;
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Primary -> PrimaryNoNewArray 
static void ptPrimary_PrimaryNoNewArray(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimaryNoNewArray);
  auto t = new TPrimary;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryV::PrimaryNoNewArray;
  t->oneNt = true;
  t->primaryNoNewArray = reinterpret_cast<TPrimaryNoNewArray *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Primary -> ArrayCreationExpression 
static void ptPrimary_ArrayCreationExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayCreationExpression);
  auto t = new TPrimary;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryV::ArrayCreationExpression;
  t->oneNt = true;
  t->arrayCreationExpression = reinterpret_cast<TArrayCreationExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> Literal 
static void ptPrimaryNoNewArray_Literal(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Literal);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::Literal;
  t->oneNt = true;
  t->literal = reinterpret_cast<TLiteral *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> This2 
static void ptPrimaryNoNewArray_This2(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::This2);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::This2;
  t->oneNt = true;
  t->this2 = reinterpret_cast<TThis2 *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> ParenthesizedExpression 
static void ptPrimaryNoNewArray_ParenthesizedExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ParenthesizedExpression);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::ParenthesizedExpression;
  t->oneNt = true;
  t->parenthesizedExpression = reinterpret_cast<TParenthesizedExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> ClassInstanceCreationExpression 
static void ptPrimaryNoNewArray_ClassInstanceCreationExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassInstanceCreationExpression);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::ClassInstanceCreationExpression;
  t->oneNt = true;
  t->classInstanceCreationExpression = reinterpret_cast<TClassInstanceCreationExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> FieldAccess 
static void ptPrimaryNoNewArray_FieldAccess(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FieldAccess);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::FieldAccess;
  t->oneNt = true;
  t->fieldAccess = reinterpret_cast<TFieldAccess *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> MethodInvocation 
static void ptPrimaryNoNewArray_MethodInvocation(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodInvocation);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::MethodInvocation;
  t->oneNt = true;
  t->methodInvocation = reinterpret_cast<TMethodInvocation *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> ArrayAccess 
static void ptPrimaryNoNewArray_ArrayAccess(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayAccess);
  auto t = new TPrimaryNoNewArray;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TPrimaryNoNewArrayV::ArrayAccess;
  t->oneNt = true;
  t->arrayAccess = reinterpret_cast<TArrayAccess *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// This2 -> this 
static void ptThis2_This2(vector<Tree *> *stack) {
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
static void ptParenthesizedExpression_LParExpressionRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TParenthesizedExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TParenthesizedExpressionV::LParExpressionRPar;
  t->oneNt = false;
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ClassInstanceCreationExpression -> new ClassType ( ) 
static void ptClassInstanceCreationExpression_NewClassTypeLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassType);
  auto t = new TClassInstanceCreationExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TClassInstanceCreationExpressionV::NewClassTypeLParRPar;
  t->oneNt = false;
  t->classType = reinterpret_cast<TClassType *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ClassInstanceCreationExpression -> new ClassType ( ArgumentList ) 
static void ptClassInstanceCreationExpression_NewClassTypeLParArgumentListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassType);
  assert((*stack)[n - 1]->type == NonTerminalType::ArgumentList);
  auto t = new TClassInstanceCreationExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TClassInstanceCreationExpressionV::NewClassTypeLParArgumentListRPar;
  t->oneNt = false;
  t->classType = reinterpret_cast<TClassType *>((*stack)[n - 2]);
  t->argumentList = reinterpret_cast<TArgumentList *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArgumentList -> Expression 
static void ptArgumentList_Expression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TArgumentList;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TArgumentListV::Expression;
  t->oneNt = true;
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ArgumentList -> ArgumentList , Expression 
static void ptArgumentList_ArgumentListComExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ArgumentList);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TArgumentList;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TArgumentListV::ArgumentListComExpression;
  t->oneNt = false;
  t->argumentList = reinterpret_cast<TArgumentList *>((*stack)[n - 2]);
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayCreationExpression -> new PrimitiveType [ Expression ] 
static void ptArrayCreationExpression_NewPrimitiveTypeLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PrimitiveType);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TArrayCreationExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TArrayCreationExpressionV::NewPrimitiveTypeLSBrExpressionRSBr;
  t->oneNt = false;
  t->primitiveType = reinterpret_cast<TPrimitiveType *>((*stack)[n - 2]);
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayCreationExpression -> new ClassOrInterfaceType [ Expression ] 
static void ptArrayCreationExpression_NewClassOrInterfaceTypeLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassOrInterfaceType);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TArrayCreationExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TArrayCreationExpressionV::NewClassOrInterfaceTypeLSBrExpressionRSBr;
  t->oneNt = false;
  t->classOrInterfaceType = reinterpret_cast<TClassOrInterfaceType *>((*stack)[n - 2]);
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// FieldAccess -> Primary . Identifier 
static void ptFieldAccess_PrimaryDotIdentifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Primary);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TFieldAccess;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TFieldAccessV::PrimaryDotIdentifier;
  t->oneNt = false;
  t->primary = reinterpret_cast<TPrimary *>((*stack)[n - 2]);
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Name ( ) 
static void ptMethodInvocation_NameLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TMethodInvocation;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TMethodInvocationV::NameLParRPar;
  t->oneNt = false;
  t->name = reinterpret_cast<TName *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Name ( ArgumentList ) 
static void ptMethodInvocation_NameLParArgumentListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Name);
  assert((*stack)[n - 1]->type == NonTerminalType::ArgumentList);
  auto t = new TMethodInvocation;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMethodInvocationV::NameLParArgumentListRPar;
  t->oneNt = false;
  t->name = reinterpret_cast<TName *>((*stack)[n - 2]);
  t->argumentList = reinterpret_cast<TArgumentList *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Primary . Identifier ( ) 
static void ptMethodInvocation_PrimaryDotIdentifierLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Primary);
  assert((*stack)[n - 1]->type == NonTerminalType::Identifier);
  auto t = new TMethodInvocation;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMethodInvocationV::PrimaryDotIdentifierLParRPar;
  t->oneNt = false;
  t->primary = reinterpret_cast<TPrimary *>((*stack)[n - 2]);
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Primary . Identifier ( ArgumentList ) 
static void ptMethodInvocation_PrimaryDotIdentifierLParArgumentListRPar(vector<Tree *> *stack) {
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
  t->primary = reinterpret_cast<TPrimary *>((*stack)[n - 3]);
  t->identifier = reinterpret_cast<TIdentifier *>((*stack)[n - 2]);
  t->argumentList = reinterpret_cast<TArgumentList *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayAccess -> Name [ Expression ] 
static void ptArrayAccess_NameLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Name);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TArrayAccess;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TArrayAccessV::NameLSBrExpressionRSBr;
  t->oneNt = false;
  t->name = reinterpret_cast<TName *>((*stack)[n - 2]);
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayAccess -> PrimaryNoNewArray [ Expression ] 
static void ptArrayAccess_PrimaryNoNewArrayLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PrimaryNoNewArray);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TArrayAccess;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TArrayAccessV::PrimaryNoNewArrayLSBrExpressionRSBr;
  t->oneNt = false;
  t->primaryNoNewArray = reinterpret_cast<TPrimaryNoNewArray *>((*stack)[n - 2]);
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpression -> - UnaryExpression 
static void ptUnaryExpression_MinusUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TUnaryExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TUnaryExpressionV::MinusUnaryExpression;
  t->oneNt = false;
  t->unaryExpression = reinterpret_cast<TUnaryExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpression -> UnaryExpressionNotPlusMinus 
static void ptUnaryExpression_UnaryExpressionNotPlusMinus(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpressionNotPlusMinus);
  auto t = new TUnaryExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TUnaryExpressionV::UnaryExpressionNotPlusMinus;
  t->oneNt = true;
  t->unaryExpressionNotPlusMinus = reinterpret_cast<TUnaryExpressionNotPlusMinus *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> Primary 
static void ptUnaryExpressionNotPlusMinus_Primary(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Primary);
  auto t = new TUnaryExpressionNotPlusMinus;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TUnaryExpressionNotPlusMinusV::Primary;
  t->oneNt = true;
  t->primary = reinterpret_cast<TPrimary *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> Name 
static void ptUnaryExpressionNotPlusMinus_Name(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TUnaryExpressionNotPlusMinus;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TUnaryExpressionNotPlusMinusV::Name;
  t->oneNt = true;
  t->name = reinterpret_cast<TName *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> ! UnaryExpression 
static void ptUnaryExpressionNotPlusMinus_BangUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TUnaryExpressionNotPlusMinus;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TUnaryExpressionNotPlusMinusV::BangUnaryExpression;
  t->oneNt = false;
  t->unaryExpression = reinterpret_cast<TUnaryExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> CastExpression 
static void ptUnaryExpressionNotPlusMinus_CastExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::CastExpression);
  auto t = new TUnaryExpressionNotPlusMinus;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TUnaryExpressionNotPlusMinusV::CastExpression;
  t->oneNt = true;
  t->castExpression = reinterpret_cast<TCastExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( PrimitiveType ) UnaryExpression 
static void ptCastExpression_LParPrimitiveTypeRParUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PrimitiveType);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TCastExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCastExpressionV::LParPrimitiveTypeRParUnaryExpression;
  t->oneNt = false;
  t->primitiveType = reinterpret_cast<TPrimitiveType *>((*stack)[n - 2]);
  t->unaryExpression = reinterpret_cast<TUnaryExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( PrimitiveType [ ] ) UnaryExpression 
static void ptCastExpression_LParPrimitiveTypeLSBrRSBrRParUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::PrimitiveType);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TCastExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCastExpressionV::LParPrimitiveTypeLSBrRSBrRParUnaryExpression;
  t->oneNt = false;
  t->primitiveType = reinterpret_cast<TPrimitiveType *>((*stack)[n - 2]);
  t->unaryExpression = reinterpret_cast<TUnaryExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( Expression ) UnaryExpressionNotPlusMinus 
static void ptCastExpression_LParExpressionRParUnaryExpressionNotPlusMinus(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpressionNotPlusMinus);
  auto t = new TCastExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCastExpressionV::LParExpressionRParUnaryExpressionNotPlusMinus;
  t->oneNt = false;
  t->expression = reinterpret_cast<TExpression *>((*stack)[n - 2]);
  t->unaryExpressionNotPlusMinus = reinterpret_cast<TUnaryExpressionNotPlusMinus *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( Name [ ] ) UnaryExpressionNotPlusMinus 
static void ptCastExpression_LParNameLSBrRSBrRParUnaryExpressionNotPlusMinus(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::Name);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpressionNotPlusMinus);
  auto t = new TCastExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TCastExpressionV::LParNameLSBrRSBrRParUnaryExpressionNotPlusMinus;
  t->oneNt = false;
  t->name = reinterpret_cast<TName *>((*stack)[n - 2]);
  t->unaryExpressionNotPlusMinus = reinterpret_cast<TUnaryExpressionNotPlusMinus *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> UnaryExpression 
static void ptMultiplicativeExpression_UnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TMultiplicativeExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TMultiplicativeExpressionV::UnaryExpression;
  t->oneNt = true;
  t->unaryExpression = reinterpret_cast<TUnaryExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> MultiplicativeExpression * UnaryExpression 
static void ptMultiplicativeExpression_MultiplicativeExpressionStarUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::MultiplicativeExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TMultiplicativeExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMultiplicativeExpressionV::MultiplicativeExpressionStarUnaryExpression;
  t->oneNt = false;
  t->multiplicativeExpression = reinterpret_cast<TMultiplicativeExpression *>((*stack)[n - 2]);
  t->unaryExpression = reinterpret_cast<TUnaryExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> MultiplicativeExpression / UnaryExpression 
static void ptMultiplicativeExpression_MultiplicativeExpressionRSlashUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::MultiplicativeExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TMultiplicativeExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMultiplicativeExpressionV::MultiplicativeExpressionRSlashUnaryExpression;
  t->oneNt = false;
  t->multiplicativeExpression = reinterpret_cast<TMultiplicativeExpression *>((*stack)[n - 2]);
  t->unaryExpression = reinterpret_cast<TUnaryExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> MultiplicativeExpression % UnaryExpression 
static void ptMultiplicativeExpression_MultiplicativeExpressionPercUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::MultiplicativeExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TMultiplicativeExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TMultiplicativeExpressionV::MultiplicativeExpressionPercUnaryExpression;
  t->oneNt = false;
  t->multiplicativeExpression = reinterpret_cast<TMultiplicativeExpression *>((*stack)[n - 2]);
  t->unaryExpression = reinterpret_cast<TUnaryExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// AdditiveExpression -> MultiplicativeExpression 
static void ptAdditiveExpression_MultiplicativeExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MultiplicativeExpression);
  auto t = new TAdditiveExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TAdditiveExpressionV::MultiplicativeExpression;
  t->oneNt = true;
  t->multiplicativeExpression = reinterpret_cast<TMultiplicativeExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// AdditiveExpression -> AdditiveExpression + MultiplicativeExpression 
static void ptAdditiveExpression_AdditiveExpressionPlusMultiplicativeExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::AdditiveExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::MultiplicativeExpression);
  auto t = new TAdditiveExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TAdditiveExpressionV::AdditiveExpressionPlusMultiplicativeExpression;
  t->oneNt = false;
  t->additiveExpression = reinterpret_cast<TAdditiveExpression *>((*stack)[n - 2]);
  t->multiplicativeExpression = reinterpret_cast<TMultiplicativeExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// AdditiveExpression -> AdditiveExpression - MultiplicativeExpression 
static void ptAdditiveExpression_AdditiveExpressionMinusMultiplicativeExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::AdditiveExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::MultiplicativeExpression);
  auto t = new TAdditiveExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TAdditiveExpressionV::AdditiveExpressionMinusMultiplicativeExpression;
  t->oneNt = false;
  t->additiveExpression = reinterpret_cast<TAdditiveExpression *>((*stack)[n - 2]);
  t->multiplicativeExpression = reinterpret_cast<TMultiplicativeExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> AdditiveExpression 
static void ptRelationalExpression_AdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TRelationalExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TRelationalExpressionV::AdditiveExpression;
  t->oneNt = true;
  t->additiveExpression = reinterpret_cast<TAdditiveExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression < AdditiveExpression 
static void ptRelationalExpression_RelationalExpressionLeAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TRelationalExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TRelationalExpressionV::RelationalExpressionLeAdditiveExpression;
  t->oneNt = false;
  t->relationalExpression = reinterpret_cast<TRelationalExpression *>((*stack)[n - 2]);
  t->additiveExpression = reinterpret_cast<TAdditiveExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression > AdditiveExpression 
static void ptRelationalExpression_RelationalExpressionGrAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TRelationalExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TRelationalExpressionV::RelationalExpressionGrAdditiveExpression;
  t->oneNt = false;
  t->relationalExpression = reinterpret_cast<TRelationalExpression *>((*stack)[n - 2]);
  t->additiveExpression = reinterpret_cast<TAdditiveExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression <= AdditiveExpression 
static void ptRelationalExpression_RelationalExpressionLeEqAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TRelationalExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TRelationalExpressionV::RelationalExpressionLeEqAdditiveExpression;
  t->oneNt = false;
  t->relationalExpression = reinterpret_cast<TRelationalExpression *>((*stack)[n - 2]);
  t->additiveExpression = reinterpret_cast<TAdditiveExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression >= AdditiveExpression 
static void ptRelationalExpression_RelationalExpressionGrEqAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  auto t = new TRelationalExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TRelationalExpressionV::RelationalExpressionGrEqAdditiveExpression;
  t->oneNt = false;
  t->relationalExpression = reinterpret_cast<TRelationalExpression *>((*stack)[n - 2]);
  t->additiveExpression = reinterpret_cast<TAdditiveExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression instanceof ReferenceType 
static void ptRelationalExpression_RelationalExpressioninstanceofReferenceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::ReferenceType);
  auto t = new TRelationalExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TRelationalExpressionV::RelationalExpressioninstanceofReferenceType;
  t->oneNt = false;
  t->relationalExpression = reinterpret_cast<TRelationalExpression *>((*stack)[n - 2]);
  t->referenceType = reinterpret_cast<TReferenceType *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// EqualityExpression -> RelationalExpression 
static void ptEqualityExpression_RelationalExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  auto t = new TEqualityExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TEqualityExpressionV::RelationalExpression;
  t->oneNt = true;
  t->relationalExpression = reinterpret_cast<TRelationalExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// EqualityExpression -> EqualityExpression == RelationalExpression 
static void ptEqualityExpression_EqualityExpressionEqEqRelationalExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::EqualityExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  auto t = new TEqualityExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TEqualityExpressionV::EqualityExpressionEqEqRelationalExpression;
  t->oneNt = false;
  t->equalityExpression = reinterpret_cast<TEqualityExpression *>((*stack)[n - 2]);
  t->relationalExpression = reinterpret_cast<TRelationalExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// EqualityExpression -> EqualityExpression != RelationalExpression 
static void ptEqualityExpression_EqualityExpressionBangEqRelationalExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::EqualityExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  auto t = new TEqualityExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TEqualityExpressionV::EqualityExpressionBangEqRelationalExpression;
  t->oneNt = false;
  t->equalityExpression = reinterpret_cast<TEqualityExpression *>((*stack)[n - 2]);
  t->relationalExpression = reinterpret_cast<TRelationalExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// AndExpression -> EqualityExpression 
static void ptAndExpression_EqualityExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::EqualityExpression);
  auto t = new TAndExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TAndExpressionV::EqualityExpression;
  t->oneNt = true;
  t->equalityExpression = reinterpret_cast<TEqualityExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// AndExpression -> AndExpression & EqualityExpression 
static void ptAndExpression_AndExpressionAmpEqualityExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::AndExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::EqualityExpression);
  auto t = new TAndExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TAndExpressionV::AndExpressionAmpEqualityExpression;
  t->oneNt = false;
  t->andExpression = reinterpret_cast<TAndExpression *>((*stack)[n - 2]);
  t->equalityExpression = reinterpret_cast<TEqualityExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InclusiveOrExpression -> AndExpression 
static void ptInclusiveOrExpression_AndExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AndExpression);
  auto t = new TInclusiveOrExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TInclusiveOrExpressionV::AndExpression;
  t->oneNt = true;
  t->andExpression = reinterpret_cast<TAndExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// InclusiveOrExpression -> InclusiveOrExpression | AndExpression 
static void ptInclusiveOrExpression_InclusiveOrExpressionOrAndExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::InclusiveOrExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::AndExpression);
  auto t = new TInclusiveOrExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TInclusiveOrExpressionV::InclusiveOrExpressionOrAndExpression;
  t->oneNt = false;
  t->inclusiveOrExpression = reinterpret_cast<TInclusiveOrExpression *>((*stack)[n - 2]);
  t->andExpression = reinterpret_cast<TAndExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ConditionalAndExpression -> InclusiveOrExpression 
static void ptConditionalAndExpression_InclusiveOrExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InclusiveOrExpression);
  auto t = new TConditionalAndExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TConditionalAndExpressionV::InclusiveOrExpression;
  t->oneNt = true;
  t->inclusiveOrExpression = reinterpret_cast<TInclusiveOrExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ConditionalAndExpression -> ConditionalAndExpression && InclusiveOrExpression 
static void ptConditionalAndExpression_ConditionalAndExpressionAmpAmpInclusiveOrExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ConditionalAndExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::InclusiveOrExpression);
  auto t = new TConditionalAndExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TConditionalAndExpressionV::ConditionalAndExpressionAmpAmpInclusiveOrExpression;
  t->oneNt = false;
  t->conditionalAndExpression = reinterpret_cast<TConditionalAndExpression *>((*stack)[n - 2]);
  t->inclusiveOrExpression = reinterpret_cast<TInclusiveOrExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ConditionalOrExpression -> ConditionalAndExpression 
static void ptConditionalOrExpression_ConditionalAndExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ConditionalAndExpression);
  auto t = new TConditionalOrExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TConditionalOrExpressionV::ConditionalAndExpression;
  t->oneNt = true;
  t->conditionalAndExpression = reinterpret_cast<TConditionalAndExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// ConditionalOrExpression -> ConditionalOrExpression || ConditionalAndExpression 
static void ptConditionalOrExpression_ConditionalOrExpressionOrOrConditionalAndExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::ConditionalOrExpression);
  assert((*stack)[n - 1]->type == NonTerminalType::ConditionalAndExpression);
  auto t = new TConditionalOrExpression;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TConditionalOrExpressionV::ConditionalOrExpressionOrOrConditionalAndExpression;
  t->oneNt = false;
  t->conditionalOrExpression = reinterpret_cast<TConditionalOrExpression *>((*stack)[n - 2]);
  t->conditionalAndExpression = reinterpret_cast<TConditionalAndExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// AssignmentExpression -> ConditionalOrExpression 
static void ptAssignmentExpression_ConditionalOrExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ConditionalOrExpression);
  auto t = new TAssignmentExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TAssignmentExpressionV::ConditionalOrExpression;
  t->oneNt = true;
  t->conditionalOrExpression = reinterpret_cast<TConditionalOrExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// AssignmentExpression -> Assignment 
static void ptAssignmentExpression_Assignment(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Assignment);
  auto t = new TAssignmentExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TAssignmentExpressionV::Assignment;
  t->oneNt = true;
  t->assignment = reinterpret_cast<TAssignment *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Assignment -> LeftHandSide = AssignmentExpression 
static void ptAssignment_LeftHandSideEqAssignmentExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 2]->type == NonTerminalType::LeftHandSide);
  assert((*stack)[n - 1]->type == NonTerminalType::AssignmentExpression);
  auto t = new TAssignment;
  ptSetTopParents(stack, 2, t);
  ptPopulateChildrenList(t, *stack, 2);
  t->v = TAssignmentV::LeftHandSideEqAssignmentExpression;
  t->oneNt = false;
  t->leftHandSide = reinterpret_cast<TLeftHandSide *>((*stack)[n - 2]);
  t->assignmentExpression = reinterpret_cast<TAssignmentExpression *>((*stack)[n - 1]);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// LeftHandSide -> Name 
static void ptLeftHandSide_Name(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TLeftHandSide;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLeftHandSideV::Name;
  t->oneNt = true;
  t->name = reinterpret_cast<TName *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// LeftHandSide -> FieldAccess 
static void ptLeftHandSide_FieldAccess(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FieldAccess);
  auto t = new TLeftHandSide;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLeftHandSideV::FieldAccess;
  t->oneNt = true;
  t->fieldAccess = reinterpret_cast<TFieldAccess *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// LeftHandSide -> ArrayAccess 
static void ptLeftHandSide_ArrayAccess(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayAccess);
  auto t = new TLeftHandSide;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TLeftHandSideV::ArrayAccess;
  t->oneNt = true;
  t->arrayAccess = reinterpret_cast<TArrayAccess *>((*stack)[n - 1]);
  stack->pop_back();
  stack->push_back(t);
}

// Expression -> AssignmentExpression 
static void ptExpression_AssignmentExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AssignmentExpression);
  auto t = new TExpression;
  ptSetTopParents(stack, 1, t);
  ptPopulateChildrenList(t, *stack, 1);
  t->v = TExpressionV::AssignmentExpression;
  t->oneNt = true;
  t->assignmentExpression = reinterpret_cast<TAssignmentExpression *>((*stack)[n - 1]);
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
    ptFieldDeclaration_ModifiersVariableDeclarationSCol, 
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
    ptLocalVariableDeclarationStatement_VariableDeclarationSCol, 
    ptVariableDeclaration_TypeVariableDeclarator, 
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
    ptConditionalAndExpression_ConditionalAndExpressionAmpAmpInclusiveOrExpression, 
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
