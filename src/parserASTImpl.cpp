#include "parserASTBase.h"
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
  t->variant = NTGoalVariants::BOFCompilationUnitEof;
  t->compilationUnit = dynamic_cast<TreeCompilationUnit *>((*stack)[n - 1]);
  assert(t->compilationUnit);
  stack->pop_back();
  stack->push_back(t);
}

// Literal -> IntegerLiteral 
void parserASTLiteral_IntegerLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeLiteral;
  t->variant = NTLiteralVariants::IntegerLiteral;
  stack->push_back(t);
}

// Literal -> BooleanLiteral 
void parserASTLiteral_BooleanLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeLiteral;
  t->variant = NTLiteralVariants::BooleanLiteral;
  stack->push_back(t);
}

// Literal -> CharacterLiteral 
void parserASTLiteral_CharacterLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeLiteral;
  t->variant = NTLiteralVariants::CharacterLiteral;
  stack->push_back(t);
}

// Literal -> StringLiteral 
void parserASTLiteral_StringLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeLiteral;
  t->variant = NTLiteralVariants::StringLiteral;
  stack->push_back(t);
}

// Literal -> NullLiteral 
void parserASTLiteral_NullLiteral(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeLiteral;
  t->variant = NTLiteralVariants::NullLiteral;
  stack->push_back(t);
}

// Type -> PrimitiveType 
void parserASTType_PrimitiveType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimitiveType);
  auto t = new TreeType;
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
  t->variant = NTTypeVariants::ReferenceType;
  t->referenceType = dynamic_cast<TreeReferenceType *>((*stack)[n - 1]);
  assert(t->referenceType);
  stack->pop_back();
  stack->push_back(t);
}

// PrimitiveType -> NumericType 
void parserASTPrimitiveType_NumericType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::NumericType);
  auto t = new TreePrimitiveType;
  t->variant = NTPrimitiveTypeVariants::NumericType;
  t->numericType = dynamic_cast<TreeNumericType *>((*stack)[n - 1]);
  assert(t->numericType);
  stack->pop_back();
  stack->push_back(t);
}

// PrimitiveType -> boolean 
void parserASTPrimitiveType_boolean(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreePrimitiveType;
  t->variant = NTPrimitiveTypeVariants::boolean;
  stack->push_back(t);
}

// NumericType -> IntegralType 
void parserASTNumericType_IntegralType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::IntegralType);
  auto t = new TreeNumericType;
  t->variant = NTNumericTypeVariants::IntegralType;
  t->integralType = dynamic_cast<TreeIntegralType *>((*stack)[n - 1]);
  assert(t->integralType);
  stack->pop_back();
  stack->push_back(t);
}

// IntegralType -> byte 
void parserASTIntegralType_byte(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeIntegralType;
  t->variant = NTIntegralTypeVariants::byte;
  stack->push_back(t);
}

// IntegralType -> short 
void parserASTIntegralType_Short(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeIntegralType;
  t->variant = NTIntegralTypeVariants::Short;
  stack->push_back(t);
}

// IntegralType -> int 
void parserASTIntegralType_Int(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeIntegralType;
  t->variant = NTIntegralTypeVariants::Int;
  stack->push_back(t);
}

// IntegralType -> char 
void parserASTIntegralType_Char(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeIntegralType;
  t->variant = NTIntegralTypeVariants::Char;
  stack->push_back(t);
}

// ReferenceType -> ClassOrInterfaceType 
void parserASTReferenceType_ClassOrInterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassOrInterfaceType);
  auto t = new TreeReferenceType;
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
  t->variant = NTArrayTypeVariants::NameLSBrRSBr;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// ArrayType -> ArrayType [ ] 
void parserASTArrayType_ArrayTypeLSBrRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayType);
  auto t = new TreeArrayType;
  t->variant = NTArrayTypeVariants::ArrayTypeLSBrRSBr;
  t->arrayType = dynamic_cast<TreeArrayType *>((*stack)[n - 1]);
  assert(t->arrayType);
  stack->pop_back();
  stack->push_back(t);
}

// Name -> SimpleName 
void parserASTName_SimpleName(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::SimpleName);
  auto t = new TreeName;
  t->variant = NTNameVariants::SimpleName;
  t->simpleName = dynamic_cast<TreeSimpleName *>((*stack)[n - 1]);
  assert(t->simpleName);
  stack->pop_back();
  stack->push_back(t);
}

// Name -> QualifiedName 
void parserASTName_QualifiedName(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::QualifiedName);
  auto t = new TreeName;
  t->variant = NTNameVariants::QualifiedName;
  t->qualifiedName = dynamic_cast<TreeQualifiedName *>((*stack)[n - 1]);
  assert(t->qualifiedName);
  stack->pop_back();
  stack->push_back(t);
}

// SimpleName -> Identifier 
void parserASTSimpleName_Identifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeSimpleName;
  t->variant = NTSimpleNameVariants::Identifier;
  stack->push_back(t);
}

// QualifiedName -> Name . Identifier 
void parserASTQualifiedName_NameDotIdentifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TreeQualifiedName;
  t->variant = NTQualifiedNameVariants::NameDotIdentifier;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
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
  assert((*stack)[n - 1]->type == NonTerminalType::PackageDeclaration);
  assert((*stack)[n - 2]->type == NonTerminalType::ImportDeclarations);
  auto t = new TreeCompilationUnit;
  t->variant = NTCompilationUnitVariants::PackageDeclarationImportDeclarations;
  t->packageDeclaration = dynamic_cast<TreePackageDeclaration *>((*stack)[n - 1]);
  assert(t->packageDeclaration);
  t->importDeclarations = dynamic_cast<TreeImportDeclarations *>((*stack)[n - 2]);
  assert(t->importDeclarations);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> TypeDeclarations 
void parserASTCompilationUnit_TypeDeclarations(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclarations);
  auto t = new TreeCompilationUnit;
  t->variant = NTCompilationUnitVariants::TypeDeclarations;
  t->typeDeclarations = dynamic_cast<TreeTypeDeclarations *>((*stack)[n - 1]);
  assert(t->typeDeclarations);
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> PackageDeclaration TypeDeclarations 
void parserASTCompilationUnit_PackageDeclarationTypeDeclarations(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::PackageDeclaration);
  assert((*stack)[n - 2]->type == NonTerminalType::TypeDeclarations);
  auto t = new TreeCompilationUnit;
  t->variant = NTCompilationUnitVariants::PackageDeclarationTypeDeclarations;
  t->packageDeclaration = dynamic_cast<TreePackageDeclaration *>((*stack)[n - 1]);
  assert(t->packageDeclaration);
  t->typeDeclarations = dynamic_cast<TreeTypeDeclarations *>((*stack)[n - 2]);
  assert(t->typeDeclarations);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> ImportDeclarations TypeDeclarations 
void parserASTCompilationUnit_ImportDeclarationsTypeDeclarations(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclarations);
  assert((*stack)[n - 2]->type == NonTerminalType::TypeDeclarations);
  auto t = new TreeCompilationUnit;
  t->variant = NTCompilationUnitVariants::ImportDeclarationsTypeDeclarations;
  t->importDeclarations = dynamic_cast<TreeImportDeclarations *>((*stack)[n - 1]);
  assert(t->importDeclarations);
  t->typeDeclarations = dynamic_cast<TreeTypeDeclarations *>((*stack)[n - 2]);
  assert(t->typeDeclarations);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CompilationUnit -> PackageDeclaration ImportDeclarations TypeDeclarations 
void parserASTCompilationUnit_PackageDeclarationImportDeclarationsTypeDeclarations(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::PackageDeclaration);
  assert((*stack)[n - 2]->type == NonTerminalType::ImportDeclarations);
  assert((*stack)[n - 3]->type == NonTerminalType::TypeDeclarations);
  auto t = new TreeCompilationUnit;
  t->variant = NTCompilationUnitVariants::PackageDeclarationImportDeclarationsTypeDeclarations;
  t->packageDeclaration = dynamic_cast<TreePackageDeclaration *>((*stack)[n - 1]);
  assert(t->packageDeclaration);
  t->importDeclarations = dynamic_cast<TreeImportDeclarations *>((*stack)[n - 2]);
  assert(t->importDeclarations);
  t->typeDeclarations = dynamic_cast<TreeTypeDeclarations *>((*stack)[n - 3]);
  assert(t->typeDeclarations);
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
  assert((*stack)[n - 1]->type == NonTerminalType::ImportDeclarations);
  assert((*stack)[n - 2]->type == NonTerminalType::ImportDeclaration);
  auto t = new TreeImportDeclarations;
  t->variant = NTImportDeclarationsVariants::ImportDeclarationsImportDeclaration;
  t->importDeclarations = dynamic_cast<TreeImportDeclarations *>((*stack)[n - 1]);
  assert(t->importDeclarations);
  t->importDeclaration = dynamic_cast<TreeImportDeclaration *>((*stack)[n - 2]);
  assert(t->importDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// TypeDeclarations -> TypeDeclaration 
void parserASTTypeDeclarations_TypeDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclaration);
  auto t = new TreeTypeDeclarations;
  t->variant = NTTypeDeclarationsVariants::TypeDeclaration;
  t->typeDeclaration = dynamic_cast<TreeTypeDeclaration *>((*stack)[n - 1]);
  assert(t->typeDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// TypeDeclarations -> TypeDeclarations TypeDeclaration 
void parserASTTypeDeclarations_TypeDeclarationsTypeDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::TypeDeclarations);
  assert((*stack)[n - 2]->type == NonTerminalType::TypeDeclaration);
  auto t = new TreeTypeDeclarations;
  t->variant = NTTypeDeclarationsVariants::TypeDeclarationsTypeDeclaration;
  t->typeDeclarations = dynamic_cast<TreeTypeDeclarations *>((*stack)[n - 1]);
  assert(t->typeDeclarations);
  t->typeDeclaration = dynamic_cast<TreeTypeDeclaration *>((*stack)[n - 2]);
  assert(t->typeDeclaration);
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
  t->variant = NTTypeDeclarationVariants::SCol;
  stack->push_back(t);
}

// Modifiers -> Modifier 
void parserASTModifiers_Modifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifier);
  auto t = new TreeModifiers;
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
  assert((*stack)[n - 1]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Modifier);
  auto t = new TreeModifiers;
  t->variant = NTModifiersVariants::ModifiersModifier;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 1]);
  assert(t->modifiers);
  t->modifier = dynamic_cast<TreeModifier *>((*stack)[n - 2]);
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
  t->variant = NTModifierVariants::Public;
  stack->push_back(t);
}

// Modifier -> protected 
void parserASTModifier_Protected(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeModifier;
  t->variant = NTModifierVariants::Protected;
  stack->push_back(t);
}

// Modifier -> static 
void parserASTModifier_Static(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeModifier;
  t->variant = NTModifierVariants::Static;
  stack->push_back(t);
}

// Modifier -> abstract 
void parserASTModifier_abstract(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeModifier;
  t->variant = NTModifierVariants::abstract;
  stack->push_back(t);
}

// Modifier -> final 
void parserASTModifier_final(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeModifier;
  t->variant = NTModifierVariants::final;
  stack->push_back(t);
}

// Modifier -> native 
void parserASTModifier_native(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeModifier;
  t->variant = NTModifierVariants::native;
  stack->push_back(t);
}

// ClassDeclaration -> class Identifier ClassBody 
void parserASTClassDeclaration_ClassIdentifierClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  t->variant = NTClassDeclarationVariants::ClassIdentifierClassBody;
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 1]);
  assert(t->classBody);
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier ClassBody 
void parserASTClassDeclaration_ModifiersClassIdentifierClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  t->variant = NTClassDeclarationVariants::ModifiersClassIdentifierClassBody;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 1]);
  assert(t->modifiers);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 2]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> class Identifier Super ClassBody 
void parserASTClassDeclaration_ClassIdentifierSuperClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::Super);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  t->variant = NTClassDeclarationVariants::ClassIdentifierSuperClassBody;
  t->super = dynamic_cast<TreeSuper *>((*stack)[n - 1]);
  assert(t->super);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 2]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier Super ClassBody 
void parserASTClassDeclaration_ModifiersClassIdentifierSuperClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Super);
  assert((*stack)[n - 3]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  t->variant = NTClassDeclarationVariants::ModifiersClassIdentifierSuperClassBody;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 1]);
  assert(t->modifiers);
  t->super = dynamic_cast<TreeSuper *>((*stack)[n - 2]);
  assert(t->super);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 3]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> class Identifier Interfaces ClassBody 
void parserASTClassDeclaration_ClassIdentifierInterfacesClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::Interfaces);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  t->variant = NTClassDeclarationVariants::ClassIdentifierInterfacesClassBody;
  t->interfaces = dynamic_cast<TreeInterfaces *>((*stack)[n - 1]);
  assert(t->interfaces);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 2]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier Interfaces ClassBody 
void parserASTClassDeclaration_ModifiersClassIdentifierInterfacesClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Interfaces);
  assert((*stack)[n - 3]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  t->variant = NTClassDeclarationVariants::ModifiersClassIdentifierInterfacesClassBody;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 1]);
  assert(t->modifiers);
  t->interfaces = dynamic_cast<TreeInterfaces *>((*stack)[n - 2]);
  assert(t->interfaces);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 3]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> class Identifier Super Interfaces ClassBody 
void parserASTClassDeclaration_ClassIdentifierSuperInterfacesClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::Super);
  assert((*stack)[n - 2]->type == NonTerminalType::Interfaces);
  assert((*stack)[n - 3]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  t->variant = NTClassDeclarationVariants::ClassIdentifierSuperInterfacesClassBody;
  t->super = dynamic_cast<TreeSuper *>((*stack)[n - 1]);
  assert(t->super);
  t->interfaces = dynamic_cast<TreeInterfaces *>((*stack)[n - 2]);
  assert(t->interfaces);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 3]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassDeclaration -> Modifiers class Identifier Super Interfaces ClassBody 
void parserASTClassDeclaration_ModifiersClassIdentifierSuperInterfacesClassBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 4);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Super);
  assert((*stack)[n - 3]->type == NonTerminalType::Interfaces);
  assert((*stack)[n - 4]->type == NonTerminalType::ClassBody);
  auto t = new TreeClassDeclaration;
  t->variant = NTClassDeclarationVariants::ModifiersClassIdentifierSuperInterfacesClassBody;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 1]);
  assert(t->modifiers);
  t->super = dynamic_cast<TreeSuper *>((*stack)[n - 2]);
  assert(t->super);
  t->interfaces = dynamic_cast<TreeInterfaces *>((*stack)[n - 3]);
  assert(t->interfaces);
  t->classBody = dynamic_cast<TreeClassBody *>((*stack)[n - 4]);
  assert(t->classBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// Super -> extends ClassType 
void parserASTSuper_extendsClassType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassType);
  auto t = new TreeSuper;
  t->variant = NTSuperVariants::extendsClassType;
  t->classType = dynamic_cast<TreeClassType *>((*stack)[n - 1]);
  assert(t->classType);
  stack->pop_back();
  stack->push_back(t);
}

// Interfaces -> implements InterfaceTypeList 
void parserASTInterfaces_implementsInterfaceTypeList(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceTypeList);
  auto t = new TreeInterfaces;
  t->variant = NTInterfacesVariants::implementsInterfaceTypeList;
  t->interfaceTypeList = dynamic_cast<TreeInterfaceTypeList *>((*stack)[n - 1]);
  assert(t->interfaceTypeList);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceTypeList -> InterfaceType 
void parserASTInterfaceTypeList_InterfaceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceType);
  auto t = new TreeInterfaceTypeList;
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
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceTypeList);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceType);
  auto t = new TreeInterfaceTypeList;
  t->variant = NTInterfaceTypeListVariants::InterfaceTypeListComInterfaceType;
  t->interfaceTypeList = dynamic_cast<TreeInterfaceTypeList *>((*stack)[n - 1]);
  assert(t->interfaceTypeList);
  t->interfaceType = dynamic_cast<TreeInterfaceType *>((*stack)[n - 2]);
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
  t->variant = NTClassBodyVariants::LCBrRCBr;
  stack->push_back(t);
}

// ClassBody -> { ClassBodyDeclarations } 
void parserASTClassBody_LCBrClassBodyDeclarationsRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBodyDeclarations);
  auto t = new TreeClassBody;
  t->variant = NTClassBodyVariants::LCBrClassBodyDeclarationsRCBr;
  t->classBodyDeclarations = dynamic_cast<TreeClassBodyDeclarations *>((*stack)[n - 1]);
  assert(t->classBodyDeclarations);
  stack->pop_back();
  stack->push_back(t);
}

// ClassBodyDeclarations -> ClassBodyDeclaration 
void parserASTClassBodyDeclarations_ClassBodyDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBodyDeclaration);
  auto t = new TreeClassBodyDeclarations;
  t->variant = NTClassBodyDeclarationsVariants::ClassBodyDeclaration;
  t->classBodyDeclaration = dynamic_cast<TreeClassBodyDeclaration *>((*stack)[n - 1]);
  assert(t->classBodyDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ClassBodyDeclarations -> ClassBodyDeclarations ClassBodyDeclaration 
void parserASTClassBodyDeclarations_ClassBodyDeclarationsClassBodyDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassBodyDeclarations);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassBodyDeclaration);
  auto t = new TreeClassBodyDeclarations;
  t->variant = NTClassBodyDeclarationsVariants::ClassBodyDeclarationsClassBodyDeclaration;
  t->classBodyDeclarations = dynamic_cast<TreeClassBodyDeclarations *>((*stack)[n - 1]);
  assert(t->classBodyDeclarations);
  t->classBodyDeclaration = dynamic_cast<TreeClassBodyDeclaration *>((*stack)[n - 2]);
  assert(t->classBodyDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassBodyDeclaration -> ClassMemberDeclaration 
void parserASTClassBodyDeclaration_ClassMemberDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassMemberDeclaration);
  auto t = new TreeClassBodyDeclaration;
  t->variant = NTClassBodyDeclarationVariants::ClassMemberDeclaration;
  t->classMemberDeclaration = dynamic_cast<TreeClassMemberDeclaration *>((*stack)[n - 1]);
  assert(t->classMemberDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ClassBodyDeclaration -> StaticInitializer 
void parserASTClassBodyDeclaration_StaticInitializer(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StaticInitializer);
  auto t = new TreeClassBodyDeclaration;
  t->variant = NTClassBodyDeclarationVariants::StaticInitializer;
  t->staticInitializer = dynamic_cast<TreeStaticInitializer *>((*stack)[n - 1]);
  assert(t->staticInitializer);
  stack->pop_back();
  stack->push_back(t);
}

// ClassBodyDeclaration -> ConstructorDeclaration 
void parserASTClassBodyDeclaration_ConstructorDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ConstructorDeclaration);
  auto t = new TreeClassBodyDeclaration;
  t->variant = NTClassBodyDeclarationVariants::ConstructorDeclaration;
  t->constructorDeclaration = dynamic_cast<TreeConstructorDeclaration *>((*stack)[n - 1]);
  assert(t->constructorDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ClassMemberDeclaration -> FieldDeclaration 
void parserASTClassMemberDeclaration_FieldDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FieldDeclaration);
  auto t = new TreeClassMemberDeclaration;
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
  t->variant = NTClassMemberDeclarationVariants::MethodDeclaration;
  t->methodDeclaration = dynamic_cast<TreeMethodDeclaration *>((*stack)[n - 1]);
  assert(t->methodDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// FieldDeclaration -> Type VariableDeclarator ; 
void parserASTFieldDeclaration_TypeVariableDeclaratorSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::Type);
  assert((*stack)[n - 2]->type == NonTerminalType::VariableDeclarator);
  auto t = new TreeFieldDeclaration;
  t->variant = NTFieldDeclarationVariants::TypeVariableDeclaratorSCol;
  t->type = dynamic_cast<TreeType *>((*stack)[n - 1]);
  assert(t->type);
  t->variableDeclarator = dynamic_cast<TreeVariableDeclarator *>((*stack)[n - 2]);
  assert(t->variableDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// FieldDeclaration -> Modifiers Type VariableDeclarator ; 
void parserASTFieldDeclaration_ModifiersTypeVariableDeclaratorSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 3]->type == NonTerminalType::VariableDeclarator);
  auto t = new TreeFieldDeclaration;
  t->variant = NTFieldDeclarationVariants::ModifiersTypeVariableDeclaratorSCol;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 1]);
  assert(t->modifiers);
  t->type = dynamic_cast<TreeType *>((*stack)[n - 2]);
  assert(t->type);
  t->variableDeclarator = dynamic_cast<TreeVariableDeclarator *>((*stack)[n - 3]);
  assert(t->variableDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// VariableDeclarator -> VariableDeclaratorId 
void parserASTVariableDeclarator_VariableDeclaratorId(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableDeclaratorId);
  auto t = new TreeVariableDeclarator;
  t->variant = NTVariableDeclaratorVariants::VariableDeclaratorId;
  t->variableDeclaratorId = dynamic_cast<TreeVariableDeclaratorId *>((*stack)[n - 1]);
  assert(t->variableDeclaratorId);
  stack->pop_back();
  stack->push_back(t);
}

// VariableDeclarator -> VariableDeclaratorId = VariableInitializer 
void parserASTVariableDeclarator_VariableDeclaratorIdEqVariableInitializer(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableDeclaratorId);
  assert((*stack)[n - 2]->type == NonTerminalType::VariableInitializer);
  auto t = new TreeVariableDeclarator;
  t->variant = NTVariableDeclaratorVariants::VariableDeclaratorIdEqVariableInitializer;
  t->variableDeclaratorId = dynamic_cast<TreeVariableDeclaratorId *>((*stack)[n - 1]);
  assert(t->variableDeclaratorId);
  t->variableInitializer = dynamic_cast<TreeVariableInitializer *>((*stack)[n - 2]);
  assert(t->variableInitializer);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// VariableDeclaratorId -> Identifier 
void parserASTVariableDeclaratorId_Identifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeVariableDeclaratorId;
  t->variant = NTVariableDeclaratorIdVariants::Identifier;
  stack->push_back(t);
}

// VariableDeclaratorId -> VariableDeclaratorId [ ] 
void parserASTVariableDeclaratorId_VariableDeclaratorIdLSBrRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableDeclaratorId);
  auto t = new TreeVariableDeclaratorId;
  t->variant = NTVariableDeclaratorIdVariants::VariableDeclaratorIdLSBrRSBr;
  t->variableDeclaratorId = dynamic_cast<TreeVariableDeclaratorId *>((*stack)[n - 1]);
  assert(t->variableDeclaratorId);
  stack->pop_back();
  stack->push_back(t);
}

// VariableInitializer -> Expression 
void parserASTVariableInitializer_Expression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreeVariableInitializer;
  t->variant = NTVariableInitializerVariants::Expression;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->push_back(t);
}

// VariableInitializer -> ArrayInitializer 
void parserASTVariableInitializer_ArrayInitializer(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ArrayInitializer);
  auto t = new TreeVariableInitializer;
  t->variant = NTVariableInitializerVariants::ArrayInitializer;
  t->arrayInitializer = dynamic_cast<TreeArrayInitializer *>((*stack)[n - 1]);
  assert(t->arrayInitializer);
  stack->pop_back();
  stack->push_back(t);
}

// MethodDeclaration -> MethodHeader MethodBody 
void parserASTMethodDeclaration_MethodHeaderMethodBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodHeader);
  assert((*stack)[n - 2]->type == NonTerminalType::MethodBody);
  auto t = new TreeMethodDeclaration;
  t->variant = NTMethodDeclarationVariants::MethodHeaderMethodBody;
  t->methodHeader = dynamic_cast<TreeMethodHeader *>((*stack)[n - 1]);
  assert(t->methodHeader);
  t->methodBody = dynamic_cast<TreeMethodBody *>((*stack)[n - 2]);
  assert(t->methodBody);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> Type MethodDeclarator 
void parserASTMethodHeader_TypeMethodDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::Type);
  assert((*stack)[n - 2]->type == NonTerminalType::MethodDeclarator);
  auto t = new TreeMethodHeader;
  t->variant = NTMethodHeaderVariants::TypeMethodDeclarator;
  t->type = dynamic_cast<TreeType *>((*stack)[n - 1]);
  assert(t->type);
  t->methodDeclarator = dynamic_cast<TreeMethodDeclarator *>((*stack)[n - 2]);
  assert(t->methodDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodHeader -> Modifiers Type MethodDeclarator 
void parserASTMethodHeader_ModifiersTypeMethodDeclarator(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::Type);
  assert((*stack)[n - 3]->type == NonTerminalType::MethodDeclarator);
  auto t = new TreeMethodHeader;
  t->variant = NTMethodHeaderVariants::ModifiersTypeMethodDeclarator;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 1]);
  assert(t->modifiers);
  t->type = dynamic_cast<TreeType *>((*stack)[n - 2]);
  assert(t->type);
  t->methodDeclarator = dynamic_cast<TreeMethodDeclarator *>((*stack)[n - 3]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::MethodDeclarator);
  auto t = new TreeMethodHeader;
  t->variant = NTMethodHeaderVariants::ModifiersVoidMethodDeclarator;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 1]);
  assert(t->modifiers);
  t->methodDeclarator = dynamic_cast<TreeMethodDeclarator *>((*stack)[n - 2]);
  assert(t->methodDeclarator);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodDeclarator -> Identifier ( ) 
void parserASTMethodDeclarator_IdentifierLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeMethodDeclarator;
  t->variant = NTMethodDeclaratorVariants::IdentifierLParRPar;
  stack->push_back(t);
}

// MethodDeclarator -> Identifier ( FormalParameterList ) 
void parserASTMethodDeclarator_IdentifierLParFormalParameterListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameterList);
  auto t = new TreeMethodDeclarator;
  t->variant = NTMethodDeclaratorVariants::IdentifierLParFormalParameterListRPar;
  t->formalParameterList = dynamic_cast<TreeFormalParameterList *>((*stack)[n - 1]);
  assert(t->formalParameterList);
  stack->pop_back();
  stack->push_back(t);
}

// MethodDeclarator -> MethodDeclarator [ ] 
void parserASTMethodDeclarator_MethodDeclaratorLSBrRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodDeclarator);
  auto t = new TreeMethodDeclarator;
  t->variant = NTMethodDeclaratorVariants::MethodDeclaratorLSBrRSBr;
  t->methodDeclarator = dynamic_cast<TreeMethodDeclarator *>((*stack)[n - 1]);
  assert(t->methodDeclarator);
  stack->pop_back();
  stack->push_back(t);
}

// FormalParameterList -> FormalParameter 
void parserASTFormalParameterList_FormalParameter(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameter);
  auto t = new TreeFormalParameterList;
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
  assert((*stack)[n - 1]->type == NonTerminalType::FormalParameterList);
  assert((*stack)[n - 2]->type == NonTerminalType::FormalParameter);
  auto t = new TreeFormalParameterList;
  t->variant = NTFormalParameterListVariants::FormalParameterListComFormalParameter;
  t->formalParameterList = dynamic_cast<TreeFormalParameterList *>((*stack)[n - 1]);
  assert(t->formalParameterList);
  t->formalParameter = dynamic_cast<TreeFormalParameter *>((*stack)[n - 2]);
  assert(t->formalParameter);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// FormalParameter -> Type VariableDeclaratorId 
void parserASTFormalParameter_TypeVariableDeclaratorId(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::Type);
  assert((*stack)[n - 2]->type == NonTerminalType::VariableDeclaratorId);
  auto t = new TreeFormalParameter;
  t->variant = NTFormalParameterVariants::TypeVariableDeclaratorId;
  t->type = dynamic_cast<TreeType *>((*stack)[n - 1]);
  assert(t->type);
  t->variableDeclaratorId = dynamic_cast<TreeVariableDeclaratorId *>((*stack)[n - 2]);
  assert(t->variableDeclaratorId);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ClassTypeList -> ClassType 
void parserASTClassTypeList_ClassType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassType);
  auto t = new TreeClassTypeList;
  t->variant = NTClassTypeListVariants::ClassType;
  t->classType = dynamic_cast<TreeClassType *>((*stack)[n - 1]);
  assert(t->classType);
  stack->pop_back();
  stack->push_back(t);
}

// ClassTypeList -> ClassTypeList , ClassType 
void parserASTClassTypeList_ClassTypeListComClassType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassTypeList);
  assert((*stack)[n - 2]->type == NonTerminalType::ClassType);
  auto t = new TreeClassTypeList;
  t->variant = NTClassTypeListVariants::ClassTypeListComClassType;
  t->classTypeList = dynamic_cast<TreeClassTypeList *>((*stack)[n - 1]);
  assert(t->classTypeList);
  t->classType = dynamic_cast<TreeClassType *>((*stack)[n - 2]);
  assert(t->classType);
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
  t->variant = NTMethodBodyVariants::Block;
  t->block = dynamic_cast<TreeBlock *>((*stack)[n - 1]);
  assert(t->block);
  stack->pop_back();
  stack->push_back(t);
}

// MethodBody -> ; 
void parserASTMethodBody_SCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeMethodBody;
  t->variant = NTMethodBodyVariants::SCol;
  stack->push_back(t);
}

// StaticInitializer -> static Block 
void parserASTStaticInitializer_StaticBlock(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Block);
  auto t = new TreeStaticInitializer;
  t->variant = NTStaticInitializerVariants::StaticBlock;
  t->block = dynamic_cast<TreeBlock *>((*stack)[n - 1]);
  assert(t->block);
  stack->pop_back();
  stack->push_back(t);
}

// ConstructorDeclaration -> ConstructorDeclarator ConstructorBody 
void parserASTConstructorDeclaration_ConstructorDeclaratorConstructorBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::ConstructorDeclarator);
  assert((*stack)[n - 2]->type == NonTerminalType::ConstructorBody);
  auto t = new TreeConstructorDeclaration;
  t->variant = NTConstructorDeclarationVariants::ConstructorDeclaratorConstructorBody;
  t->constructorDeclarator = dynamic_cast<TreeConstructorDeclarator *>((*stack)[n - 1]);
  assert(t->constructorDeclarator);
  t->constructorBody = dynamic_cast<TreeConstructorBody *>((*stack)[n - 2]);
  assert(t->constructorBody);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ConstructorDeclaration -> Modifiers ConstructorDeclarator ConstructorBody 
void parserASTConstructorDeclaration_ModifiersConstructorDeclaratorConstructorBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::ConstructorDeclarator);
  assert((*stack)[n - 3]->type == NonTerminalType::ConstructorBody);
  auto t = new TreeConstructorDeclaration;
  t->variant = NTConstructorDeclarationVariants::ModifiersConstructorDeclaratorConstructorBody;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 1]);
  assert(t->modifiers);
  t->constructorDeclarator = dynamic_cast<TreeConstructorDeclarator *>((*stack)[n - 2]);
  assert(t->constructorDeclarator);
  t->constructorBody = dynamic_cast<TreeConstructorBody *>((*stack)[n - 3]);
  assert(t->constructorBody);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ConstructorDeclarator -> SimpleName ( ) 
void parserASTConstructorDeclarator_SimpleNameLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::SimpleName);
  auto t = new TreeConstructorDeclarator;
  t->variant = NTConstructorDeclaratorVariants::SimpleNameLParRPar;
  t->simpleName = dynamic_cast<TreeSimpleName *>((*stack)[n - 1]);
  assert(t->simpleName);
  stack->pop_back();
  stack->push_back(t);
}

// ConstructorDeclarator -> SimpleName ( FormalParameterList ) 
void parserASTConstructorDeclarator_SimpleNameLParFormalParameterListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::SimpleName);
  assert((*stack)[n - 2]->type == NonTerminalType::FormalParameterList);
  auto t = new TreeConstructorDeclarator;
  t->variant = NTConstructorDeclaratorVariants::SimpleNameLParFormalParameterListRPar;
  t->simpleName = dynamic_cast<TreeSimpleName *>((*stack)[n - 1]);
  assert(t->simpleName);
  t->formalParameterList = dynamic_cast<TreeFormalParameterList *>((*stack)[n - 2]);
  assert(t->formalParameterList);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ConstructorBody -> { } 
void parserASTConstructorBody_LCBrRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeConstructorBody;
  t->variant = NTConstructorBodyVariants::LCBrRCBr;
  stack->push_back(t);
}

// ConstructorBody -> { BlockStatements } 
void parserASTConstructorBody_LCBrBlockStatementsRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::BlockStatements);
  auto t = new TreeConstructorBody;
  t->variant = NTConstructorBodyVariants::LCBrBlockStatementsRCBr;
  t->blockStatements = dynamic_cast<TreeBlockStatements *>((*stack)[n - 1]);
  assert(t->blockStatements);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> interface Identifier InterfaceBody 
void parserASTInterfaceDeclaration_interfaceIdentifierInterfaceBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceBody);
  auto t = new TreeInterfaceDeclaration;
  t->variant = NTInterfaceDeclarationVariants::interfaceIdentifierInterfaceBody;
  t->interfaceBody = dynamic_cast<TreeInterfaceBody *>((*stack)[n - 1]);
  assert(t->interfaceBody);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> Modifiers interface Identifier InterfaceBody 
void parserASTInterfaceDeclaration_ModifiersinterfaceIdentifierInterfaceBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceBody);
  auto t = new TreeInterfaceDeclaration;
  t->variant = NTInterfaceDeclarationVariants::ModifiersinterfaceIdentifierInterfaceBody;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 1]);
  assert(t->modifiers);
  t->interfaceBody = dynamic_cast<TreeInterfaceBody *>((*stack)[n - 2]);
  assert(t->interfaceBody);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> interface Identifier ExtendsInterfaces InterfaceBody 
void parserASTInterfaceDeclaration_interfaceIdentifierExtendsInterfacesInterfaceBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::ExtendsInterfaces);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceBody);
  auto t = new TreeInterfaceDeclaration;
  t->variant = NTInterfaceDeclarationVariants::interfaceIdentifierExtendsInterfacesInterfaceBody;
  t->extendsInterfaces = dynamic_cast<TreeExtendsInterfaces *>((*stack)[n - 1]);
  assert(t->extendsInterfaces);
  t->interfaceBody = dynamic_cast<TreeInterfaceBody *>((*stack)[n - 2]);
  assert(t->interfaceBody);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceDeclaration -> Modifiers interface Identifier ExtendsInterfaces InterfaceBody 
void parserASTInterfaceDeclaration_ModifiersinterfaceIdentifierExtendsInterfacesInterfaceBody(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::Modifiers);
  assert((*stack)[n - 2]->type == NonTerminalType::ExtendsInterfaces);
  assert((*stack)[n - 3]->type == NonTerminalType::InterfaceBody);
  auto t = new TreeInterfaceDeclaration;
  t->variant = NTInterfaceDeclarationVariants::ModifiersinterfaceIdentifierExtendsInterfacesInterfaceBody;
  t->modifiers = dynamic_cast<TreeModifiers *>((*stack)[n - 1]);
  assert(t->modifiers);
  t->extendsInterfaces = dynamic_cast<TreeExtendsInterfaces *>((*stack)[n - 2]);
  assert(t->extendsInterfaces);
  t->interfaceBody = dynamic_cast<TreeInterfaceBody *>((*stack)[n - 3]);
  assert(t->interfaceBody);
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
  assert((*stack)[n - 1]->type == NonTerminalType::ExtendsInterfaces);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceType);
  auto t = new TreeExtendsInterfaces;
  t->variant = NTExtendsInterfacesVariants::ExtendsInterfacesComInterfaceType;
  t->extendsInterfaces = dynamic_cast<TreeExtendsInterfaces *>((*stack)[n - 1]);
  assert(t->extendsInterfaces);
  t->interfaceType = dynamic_cast<TreeInterfaceType *>((*stack)[n - 2]);
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
  t->variant = NTInterfaceBodyVariants::LCBrRCBr;
  stack->push_back(t);
}

// InterfaceBody -> { InterfaceMemberDeclarations } 
void parserASTInterfaceBody_LCBrInterfaceMemberDeclarationsRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceMemberDeclarations);
  auto t = new TreeInterfaceBody;
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
  assert((*stack)[n - 1]->type == NonTerminalType::InterfaceMemberDeclarations);
  assert((*stack)[n - 2]->type == NonTerminalType::InterfaceMemberDeclaration);
  auto t = new TreeInterfaceMemberDeclarations;
  t->variant = NTInterfaceMemberDeclarationsVariants::InterfaceMemberDeclarationsInterfaceMemberDeclaration;
  t->interfaceMemberDeclarations = dynamic_cast<TreeInterfaceMemberDeclarations *>((*stack)[n - 1]);
  assert(t->interfaceMemberDeclarations);
  t->interfaceMemberDeclaration = dynamic_cast<TreeInterfaceMemberDeclaration *>((*stack)[n - 2]);
  assert(t->interfaceMemberDeclaration);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceMemberDeclaration -> ConstantDeclaration 
void parserASTInterfaceMemberDeclaration_ConstantDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ConstantDeclaration);
  auto t = new TreeInterfaceMemberDeclaration;
  t->variant = NTInterfaceMemberDeclarationVariants::ConstantDeclaration;
  t->constantDeclaration = dynamic_cast<TreeConstantDeclaration *>((*stack)[n - 1]);
  assert(t->constantDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// InterfaceMemberDeclaration -> AbstractMethodDeclaration 
void parserASTInterfaceMemberDeclaration_AbstractMethodDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::AbstractMethodDeclaration);
  auto t = new TreeInterfaceMemberDeclaration;
  t->variant = NTInterfaceMemberDeclarationVariants::AbstractMethodDeclaration;
  t->abstractMethodDeclaration = dynamic_cast<TreeAbstractMethodDeclaration *>((*stack)[n - 1]);
  assert(t->abstractMethodDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// ConstantDeclaration -> FieldDeclaration 
void parserASTConstantDeclaration_FieldDeclaration(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::FieldDeclaration);
  auto t = new TreeConstantDeclaration;
  t->variant = NTConstantDeclarationVariants::FieldDeclaration;
  t->fieldDeclaration = dynamic_cast<TreeFieldDeclaration *>((*stack)[n - 1]);
  assert(t->fieldDeclaration);
  stack->pop_back();
  stack->push_back(t);
}

// AbstractMethodDeclaration -> MethodHeader ; 
void parserASTAbstractMethodDeclaration_MethodHeaderSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::MethodHeader);
  auto t = new TreeAbstractMethodDeclaration;
  t->variant = NTAbstractMethodDeclarationVariants::MethodHeaderSCol;
  t->methodHeader = dynamic_cast<TreeMethodHeader *>((*stack)[n - 1]);
  assert(t->methodHeader);
  stack->pop_back();
  stack->push_back(t);
}

// ArrayInitializer -> { } 
void parserASTArrayInitializer_LCBrRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeArrayInitializer;
  t->variant = NTArrayInitializerVariants::LCBrRCBr;
  stack->push_back(t);
}

// ArrayInitializer -> { VariableInitializers } 
void parserASTArrayInitializer_LCBrVariableInitializersRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableInitializers);
  auto t = new TreeArrayInitializer;
  t->variant = NTArrayInitializerVariants::LCBrVariableInitializersRCBr;
  t->variableInitializers = dynamic_cast<TreeVariableInitializers *>((*stack)[n - 1]);
  assert(t->variableInitializers);
  stack->pop_back();
  stack->push_back(t);
}

// ArrayInitializer -> { , } 
void parserASTArrayInitializer_LCBrComRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeArrayInitializer;
  t->variant = NTArrayInitializerVariants::LCBrComRCBr;
  stack->push_back(t);
}

// ArrayInitializer -> { VariableInitializers , } 
void parserASTArrayInitializer_LCBrVariableInitializersComRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableInitializers);
  auto t = new TreeArrayInitializer;
  t->variant = NTArrayInitializerVariants::LCBrVariableInitializersComRCBr;
  t->variableInitializers = dynamic_cast<TreeVariableInitializers *>((*stack)[n - 1]);
  assert(t->variableInitializers);
  stack->pop_back();
  stack->push_back(t);
}

// VariableInitializers -> VariableInitializer 
void parserASTVariableInitializers_VariableInitializer(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableInitializer);
  auto t = new TreeVariableInitializers;
  t->variant = NTVariableInitializersVariants::VariableInitializer;
  t->variableInitializer = dynamic_cast<TreeVariableInitializer *>((*stack)[n - 1]);
  assert(t->variableInitializer);
  stack->pop_back();
  stack->push_back(t);
}

// VariableInitializers -> VariableInitializers , VariableInitializer 
void parserASTVariableInitializers_VariableInitializersComVariableInitializer(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::VariableInitializers);
  assert((*stack)[n - 2]->type == NonTerminalType::VariableInitializer);
  auto t = new TreeVariableInitializers;
  t->variant = NTVariableInitializersVariants::VariableInitializersComVariableInitializer;
  t->variableInitializers = dynamic_cast<TreeVariableInitializers *>((*stack)[n - 1]);
  assert(t->variableInitializers);
  t->variableInitializer = dynamic_cast<TreeVariableInitializer *>((*stack)[n - 2]);
  assert(t->variableInitializer);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// Block -> { } 
void parserASTBlock_LCBrRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeBlock;
  t->variant = NTBlockVariants::LCBrRCBr;
  stack->push_back(t);
}

// Block -> { BlockStatements } 
void parserASTBlock_LCBrBlockStatementsRCBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::BlockStatements);
  auto t = new TreeBlock;
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
  assert((*stack)[n - 1]->type == NonTerminalType::BlockStatements);
  assert((*stack)[n - 2]->type == NonTerminalType::BlockStatement);
  auto t = new TreeBlockStatements;
  t->variant = NTBlockStatementsVariants::BlockStatementsBlockStatement;
  t->blockStatements = dynamic_cast<TreeBlockStatements *>((*stack)[n - 1]);
  assert(t->blockStatements);
  t->blockStatement = dynamic_cast<TreeBlockStatement *>((*stack)[n - 2]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::Type);
  assert((*stack)[n - 2]->type == NonTerminalType::VariableDeclarator);
  auto t = new TreeLocalVariableDeclaration;
  t->variant = NTLocalVariableDeclarationVariants::TypeVariableDeclarator;
  t->type = dynamic_cast<TreeType *>((*stack)[n - 1]);
  assert(t->type);
  t->variableDeclarator = dynamic_cast<TreeVariableDeclarator *>((*stack)[n - 2]);
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
  t->variant = NTEmptyStatementVariants::SCol;
  stack->push_back(t);
}

// ExpressionStatement -> StatementExpression ; 
void parserASTExpressionStatement_StatementExpressionSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::StatementExpression);
  auto t = new TreeExpressionStatement;
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
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::Statement);
  auto t = new TreeIfThenStatement;
  t->variant = NTIfThenStatementVariants::IfLParExpressionRParStatement;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 2]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// IfThenElseStatement -> if ( Expression ) StatementNoShortIf else Statement 
void parserASTIfThenElseStatement_IfLParExpressionRParStatementNoShortIfElseStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::StatementNoShortIf);
  assert((*stack)[n - 3]->type == NonTerminalType::Statement);
  auto t = new TreeIfThenElseStatement;
  t->variant = NTIfThenElseStatementVariants::IfLParExpressionRParStatementNoShortIfElseStatement;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 2]);
  assert(t->statementNoShortIf);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 3]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::StatementNoShortIf);
  assert((*stack)[n - 3]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeIfThenElseStatementNoShortIf;
  t->variant = NTIfThenElseStatementNoShortIfVariants::IfLParExpressionRParStatementNoShortIfElseStatementNoShortIf;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 2]);
  assert(t->statementNoShortIf);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 3]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::Statement);
  auto t = new TreeWhileStatement;
  t->variant = NTWhileStatementVariants::WhileLParExpressionRParStatement;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 2]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// WhileStatementNoShortIf -> while ( Expression ) StatementNoShortIf 
void parserASTWhileStatementNoShortIf_WhileLParExpressionRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeWhileStatementNoShortIf;
  t->variant = NTWhileStatementNoShortIfVariants::WhileLParExpressionRParStatementNoShortIf;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 2]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  t->variant = NTForStatementVariants::ForLParForInitSColSColRParStatement;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 1]);
  assert(t->forInit);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 2]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ; Expression ; ) Statement 
void parserASTForStatement_ForLParSColExpressionSColRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  t->variant = NTForStatementVariants::ForLParSColExpressionSColRParStatement;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 2]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit ; Expression ; ) Statement 
void parserASTForStatement_ForLParForInitSColExpressionSColRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 3]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  t->variant = NTForStatementVariants::ForLParForInitSColExpressionSColRParStatement;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 1]);
  assert(t->forInit);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 3]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 2]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  t->variant = NTForStatementVariants::ForLParSColSColForUpdateRParStatement;
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 1]);
  assert(t->forUpdate);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 2]);
  assert(t->statement);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatement -> for ( ForInit ; ; ForUpdate ) Statement 
void parserASTForStatement_ForLParForInitSColSColForUpdateRParStatement(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 3]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  t->variant = NTForStatementVariants::ForLParForInitSColSColForUpdateRParStatement;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 1]);
  assert(t->forInit);
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 3]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 3]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  t->variant = NTForStatementVariants::ForLParSColExpressionSColForUpdateRParStatement;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 3]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 3]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 4]->type == NonTerminalType::Statement);
  auto t = new TreeForStatement;
  t->variant = NTForStatementVariants::ForLParForInitSColExpressionSColForUpdateRParStatement;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 1]);
  assert(t->forInit);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 3]);
  assert(t->forUpdate);
  t->statement = dynamic_cast<TreeStatement *>((*stack)[n - 4]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  t->variant = NTForStatementNoShortIfVariants::ForLParForInitSColSColRParStatementNoShortIf;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 1]);
  assert(t->forInit);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 2]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ; Expression ; ) StatementNoShortIf 
void parserASTForStatementNoShortIf_ForLParSColExpressionSColRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  t->variant = NTForStatementNoShortIfVariants::ForLParSColExpressionSColRParStatementNoShortIf;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 2]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit ; Expression ; ) StatementNoShortIf 
void parserASTForStatementNoShortIf_ForLParForInitSColExpressionSColRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 3]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  t->variant = NTForStatementNoShortIfVariants::ForLParForInitSColExpressionSColRParStatementNoShortIf;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 1]);
  assert(t->forInit);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 3]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 2]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  t->variant = NTForStatementNoShortIfVariants::ForLParSColSColForUpdateRParStatementNoShortIf;
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 1]);
  assert(t->forUpdate);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 2]);
  assert(t->statementNoShortIf);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ForStatementNoShortIf -> for ( ForInit ; ; ForUpdate ) StatementNoShortIf 
void parserASTForStatementNoShortIf_ForLParForInitSColSColForUpdateRParStatementNoShortIf(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 3]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  t->variant = NTForStatementNoShortIfVariants::ForLParForInitSColSColForUpdateRParStatementNoShortIf;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 1]);
  assert(t->forInit);
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 3]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 3]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  t->variant = NTForStatementNoShortIfVariants::ForLParSColExpressionSColForUpdateRParStatementNoShortIf;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 2]);
  assert(t->forUpdate);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 3]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::ForInit);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  assert((*stack)[n - 3]->type == NonTerminalType::ForUpdate);
  assert((*stack)[n - 4]->type == NonTerminalType::StatementNoShortIf);
  auto t = new TreeForStatementNoShortIf;
  t->variant = NTForStatementNoShortIfVariants::ForLParForInitSColExpressionSColForUpdateRParStatementNoShortIf;
  t->forInit = dynamic_cast<TreeForInit *>((*stack)[n - 1]);
  assert(t->forInit);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  t->forUpdate = dynamic_cast<TreeForUpdate *>((*stack)[n - 3]);
  assert(t->forUpdate);
  t->statementNoShortIf = dynamic_cast<TreeStatementNoShortIf *>((*stack)[n - 4]);
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
  t->variant = NTReturnStatementVariants::ReturnSCol;
  stack->push_back(t);
}

// ReturnStatement -> return Expression ; 
void parserASTReturnStatement_ReturnExpressionSCol(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreeReturnStatement;
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
  t->variant = NTPrimaryNoNewArrayVariants::Literal;
  t->literal = dynamic_cast<TreeLiteral *>((*stack)[n - 1]);
  assert(t->literal);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> this 
void parserASTPrimaryNoNewArray_This(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreePrimaryNoNewArray;
  t->variant = NTPrimaryNoNewArrayVariants::This;
  stack->push_back(t);
}

// PrimaryNoNewArray -> ( Expression ) 
void parserASTPrimaryNoNewArray_LParExpressionRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreePrimaryNoNewArray;
  t->variant = NTPrimaryNoNewArrayVariants::LParExpressionRPar;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->push_back(t);
}

// PrimaryNoNewArray -> ClassInstanceCreationExpression 
void parserASTPrimaryNoNewArray_ClassInstanceCreationExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassInstanceCreationExpression);
  auto t = new TreePrimaryNoNewArray;
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
  t->variant = NTPrimaryNoNewArrayVariants::ArrayAccess;
  t->arrayAccess = dynamic_cast<TreeArrayAccess *>((*stack)[n - 1]);
  assert(t->arrayAccess);
  stack->pop_back();
  stack->push_back(t);
}

// ClassInstanceCreationExpression -> new ClassType ( ) 
void parserASTClassInstanceCreationExpression_NewClassTypeLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassType);
  auto t = new TreeClassInstanceCreationExpression;
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
  assert((*stack)[n - 1]->type == NonTerminalType::ClassType);
  assert((*stack)[n - 2]->type == NonTerminalType::ArgumentList);
  auto t = new TreeClassInstanceCreationExpression;
  t->variant = NTClassInstanceCreationExpressionVariants::NewClassTypeLParArgumentListRPar;
  t->classType = dynamic_cast<TreeClassType *>((*stack)[n - 1]);
  assert(t->classType);
  t->argumentList = dynamic_cast<TreeArgumentList *>((*stack)[n - 2]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::ArgumentList);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  auto t = new TreeArgumentList;
  t->variant = NTArgumentListVariants::ArgumentListComExpression;
  t->argumentList = dynamic_cast<TreeArgumentList *>((*stack)[n - 1]);
  assert(t->argumentList);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayCreationExpression -> new PrimitiveType DimExprs 
void parserASTArrayCreationExpression_NewPrimitiveTypeDimExprs(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimitiveType);
  assert((*stack)[n - 2]->type == NonTerminalType::DimExprs);
  auto t = new TreeArrayCreationExpression;
  t->variant = NTArrayCreationExpressionVariants::NewPrimitiveTypeDimExprs;
  t->primitiveType = dynamic_cast<TreePrimitiveType *>((*stack)[n - 1]);
  assert(t->primitiveType);
  t->dimExprs = dynamic_cast<TreeDimExprs *>((*stack)[n - 2]);
  assert(t->dimExprs);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayCreationExpression -> new PrimitiveType DimExprs Dims 
void parserASTArrayCreationExpression_NewPrimitiveTypeDimExprsDims(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimitiveType);
  assert((*stack)[n - 2]->type == NonTerminalType::DimExprs);
  assert((*stack)[n - 3]->type == NonTerminalType::Dims);
  auto t = new TreeArrayCreationExpression;
  t->variant = NTArrayCreationExpressionVariants::NewPrimitiveTypeDimExprsDims;
  t->primitiveType = dynamic_cast<TreePrimitiveType *>((*stack)[n - 1]);
  assert(t->primitiveType);
  t->dimExprs = dynamic_cast<TreeDimExprs *>((*stack)[n - 2]);
  assert(t->dimExprs);
  t->dims = dynamic_cast<TreeDims *>((*stack)[n - 3]);
  assert(t->dims);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayCreationExpression -> new ClassOrInterfaceType DimExprs 
void parserASTArrayCreationExpression_NewClassOrInterfaceTypeDimExprs(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassOrInterfaceType);
  assert((*stack)[n - 2]->type == NonTerminalType::DimExprs);
  auto t = new TreeArrayCreationExpression;
  t->variant = NTArrayCreationExpressionVariants::NewClassOrInterfaceTypeDimExprs;
  t->classOrInterfaceType = dynamic_cast<TreeClassOrInterfaceType *>((*stack)[n - 1]);
  assert(t->classOrInterfaceType);
  t->dimExprs = dynamic_cast<TreeDimExprs *>((*stack)[n - 2]);
  assert(t->dimExprs);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayCreationExpression -> new ClassOrInterfaceType DimExprs Dims 
void parserASTArrayCreationExpression_NewClassOrInterfaceTypeDimExprsDims(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::ClassOrInterfaceType);
  assert((*stack)[n - 2]->type == NonTerminalType::DimExprs);
  assert((*stack)[n - 3]->type == NonTerminalType::Dims);
  auto t = new TreeArrayCreationExpression;
  t->variant = NTArrayCreationExpressionVariants::NewClassOrInterfaceTypeDimExprsDims;
  t->classOrInterfaceType = dynamic_cast<TreeClassOrInterfaceType *>((*stack)[n - 1]);
  assert(t->classOrInterfaceType);
  t->dimExprs = dynamic_cast<TreeDimExprs *>((*stack)[n - 2]);
  assert(t->dimExprs);
  t->dims = dynamic_cast<TreeDims *>((*stack)[n - 3]);
  assert(t->dims);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// DimExprs -> DimExpr 
void parserASTDimExprs_DimExpr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::DimExpr);
  auto t = new TreeDimExprs;
  t->variant = NTDimExprsVariants::DimExpr;
  t->dimExpr = dynamic_cast<TreeDimExpr *>((*stack)[n - 1]);
  assert(t->dimExpr);
  stack->pop_back();
  stack->push_back(t);
}

// DimExprs -> DimExprs DimExpr 
void parserASTDimExprs_DimExprsDimExpr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::DimExprs);
  assert((*stack)[n - 2]->type == NonTerminalType::DimExpr);
  auto t = new TreeDimExprs;
  t->variant = NTDimExprsVariants::DimExprsDimExpr;
  t->dimExprs = dynamic_cast<TreeDimExprs *>((*stack)[n - 1]);
  assert(t->dimExprs);
  t->dimExpr = dynamic_cast<TreeDimExpr *>((*stack)[n - 2]);
  assert(t->dimExpr);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// DimExpr -> [ Expression ] 
void parserASTDimExpr_LSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreeDimExpr;
  t->variant = NTDimExprVariants::LSBrExpressionRSBr;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  stack->pop_back();
  stack->push_back(t);
}

// Dims -> [ ] 
void parserASTDims_LSBrRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 0);
  auto t = new TreeDims;
  t->variant = NTDimsVariants::LSBrRSBr;
  stack->push_back(t);
}

// Dims -> Dims [ ] 
void parserASTDims_DimsLSBrRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Dims);
  auto t = new TreeDims;
  t->variant = NTDimsVariants::DimsLSBrRSBr;
  t->dims = dynamic_cast<TreeDims *>((*stack)[n - 1]);
  assert(t->dims);
  stack->pop_back();
  stack->push_back(t);
}

// FieldAccess -> Primary . Identifier 
void parserASTFieldAccess_PrimaryDotIdentifier(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Primary);
  auto t = new TreeFieldAccess;
  t->variant = NTFieldAccessVariants::PrimaryDotIdentifier;
  t->primary = dynamic_cast<TreePrimary *>((*stack)[n - 1]);
  assert(t->primary);
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Name ( ) 
void parserASTMethodInvocation_NameLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TreeMethodInvocation;
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
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  assert((*stack)[n - 2]->type == NonTerminalType::ArgumentList);
  auto t = new TreeMethodInvocation;
  t->variant = NTMethodInvocationVariants::NameLParArgumentListRPar;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
  t->argumentList = dynamic_cast<TreeArgumentList *>((*stack)[n - 2]);
  assert(t->argumentList);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Primary . Identifier ( ) 
void parserASTMethodInvocation_PrimaryDotIdentifierLParRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Primary);
  auto t = new TreeMethodInvocation;
  t->variant = NTMethodInvocationVariants::PrimaryDotIdentifierLParRPar;
  t->primary = dynamic_cast<TreePrimary *>((*stack)[n - 1]);
  assert(t->primary);
  stack->pop_back();
  stack->push_back(t);
}

// MethodInvocation -> Primary . Identifier ( ArgumentList ) 
void parserASTMethodInvocation_PrimaryDotIdentifierLParArgumentListRPar(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::Primary);
  assert((*stack)[n - 2]->type == NonTerminalType::ArgumentList);
  auto t = new TreeMethodInvocation;
  t->variant = NTMethodInvocationVariants::PrimaryDotIdentifierLParArgumentListRPar;
  t->primary = dynamic_cast<TreePrimary *>((*stack)[n - 1]);
  assert(t->primary);
  t->argumentList = dynamic_cast<TreeArgumentList *>((*stack)[n - 2]);
  assert(t->argumentList);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayAccess -> Name [ Expression ] 
void parserASTArrayAccess_NameLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  auto t = new TreeArrayAccess;
  t->variant = NTArrayAccessVariants::NameLSBrExpressionRSBr;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// ArrayAccess -> PrimaryNoNewArray [ Expression ] 
void parserASTArrayAccess_PrimaryNoNewArrayLSBrExpressionRSBr(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimaryNoNewArray);
  assert((*stack)[n - 2]->type == NonTerminalType::Expression);
  auto t = new TreeArrayAccess;
  t->variant = NTArrayAccessVariants::PrimaryNoNewArrayLSBrExpressionRSBr;
  t->primaryNoNewArray = dynamic_cast<TreePrimaryNoNewArray *>((*stack)[n - 1]);
  assert(t->primaryNoNewArray);
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 2]);
  assert(t->expression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// PostfixExpression -> Primary 
void parserASTPostfixExpression_Primary(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Primary);
  auto t = new TreePostfixExpression;
  t->variant = NTPostfixExpressionVariants::Primary;
  t->primary = dynamic_cast<TreePrimary *>((*stack)[n - 1]);
  assert(t->primary);
  stack->pop_back();
  stack->push_back(t);
}

// PostfixExpression -> Name 
void parserASTPostfixExpression_Name(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  auto t = new TreePostfixExpression;
  t->variant = NTPostfixExpressionVariants::Name;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpression -> - UnaryExpression 
void parserASTUnaryExpression_MinusUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeUnaryExpression;
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
  t->variant = NTUnaryExpressionVariants::UnaryExpressionNotPlusMinus;
  t->unaryExpressionNotPlusMinus = dynamic_cast<TreeUnaryExpressionNotPlusMinus *>((*stack)[n - 1]);
  assert(t->unaryExpressionNotPlusMinus);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> PostfixExpression 
void parserASTUnaryExpressionNotPlusMinus_PostfixExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::PostfixExpression);
  auto t = new TreeUnaryExpressionNotPlusMinus;
  t->variant = NTUnaryExpressionNotPlusMinusVariants::PostfixExpression;
  t->postfixExpression = dynamic_cast<TreePostfixExpression *>((*stack)[n - 1]);
  assert(t->postfixExpression);
  stack->pop_back();
  stack->push_back(t);
}

// UnaryExpressionNotPlusMinus -> ~ UnaryExpression 
void parserASTUnaryExpressionNotPlusMinus_TilUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeUnaryExpressionNotPlusMinus;
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
  assert((*stack)[n - 1]->type == NonTerminalType::PrimitiveType);
  assert((*stack)[n - 2]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeCastExpression;
  t->variant = NTCastExpressionVariants::LParPrimitiveTypeRParUnaryExpression;
  t->primitiveType = dynamic_cast<TreePrimitiveType *>((*stack)[n - 1]);
  assert(t->primitiveType);
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 2]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( PrimitiveType Dims ) UnaryExpression 
void parserASTCastExpression_LParPrimitiveTypeDimsRParUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::PrimitiveType);
  assert((*stack)[n - 2]->type == NonTerminalType::Dims);
  assert((*stack)[n - 3]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeCastExpression;
  t->variant = NTCastExpressionVariants::LParPrimitiveTypeDimsRParUnaryExpression;
  t->primitiveType = dynamic_cast<TreePrimitiveType *>((*stack)[n - 1]);
  assert(t->primitiveType);
  t->dims = dynamic_cast<TreeDims *>((*stack)[n - 2]);
  assert(t->dims);
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 3]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( Expression ) UnaryExpressionNotPlusMinus 
void parserASTCastExpression_LParExpressionRParUnaryExpressionNotPlusMinus(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  assert((*stack)[n - 2]->type == NonTerminalType::UnaryExpressionNotPlusMinus);
  auto t = new TreeCastExpression;
  t->variant = NTCastExpressionVariants::LParExpressionRParUnaryExpressionNotPlusMinus;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
  t->unaryExpressionNotPlusMinus = dynamic_cast<TreeUnaryExpressionNotPlusMinus *>((*stack)[n - 2]);
  assert(t->unaryExpressionNotPlusMinus);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// CastExpression -> ( Name Dims ) UnaryExpressionNotPlusMinus 
void parserASTCastExpression_LParNameDimsRParUnaryExpressionNotPlusMinus(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 3);
  assert((*stack)[n - 1]->type == NonTerminalType::Name);
  assert((*stack)[n - 2]->type == NonTerminalType::Dims);
  assert((*stack)[n - 3]->type == NonTerminalType::UnaryExpressionNotPlusMinus);
  auto t = new TreeCastExpression;
  t->variant = NTCastExpressionVariants::LParNameDimsRParUnaryExpressionNotPlusMinus;
  t->name = dynamic_cast<TreeName *>((*stack)[n - 1]);
  assert(t->name);
  t->dims = dynamic_cast<TreeDims *>((*stack)[n - 2]);
  assert(t->dims);
  t->unaryExpressionNotPlusMinus = dynamic_cast<TreeUnaryExpressionNotPlusMinus *>((*stack)[n - 3]);
  assert(t->unaryExpressionNotPlusMinus);
  stack->pop_back();
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
  assert((*stack)[n - 1]->type == NonTerminalType::MultiplicativeExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeMultiplicativeExpression;
  t->variant = NTMultiplicativeExpressionVariants::MultiplicativeExpressionStarUnaryExpression;
  t->multiplicativeExpression = dynamic_cast<TreeMultiplicativeExpression *>((*stack)[n - 1]);
  assert(t->multiplicativeExpression);
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 2]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> MultiplicativeExpression / UnaryExpression 
void parserASTMultiplicativeExpression_MultiplicativeExpressionRSlashUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::MultiplicativeExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeMultiplicativeExpression;
  t->variant = NTMultiplicativeExpressionVariants::MultiplicativeExpressionRSlashUnaryExpression;
  t->multiplicativeExpression = dynamic_cast<TreeMultiplicativeExpression *>((*stack)[n - 1]);
  assert(t->multiplicativeExpression);
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 2]);
  assert(t->unaryExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// MultiplicativeExpression -> MultiplicativeExpression % UnaryExpression 
void parserASTMultiplicativeExpression_MultiplicativeExpressionPercUnaryExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::MultiplicativeExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::UnaryExpression);
  auto t = new TreeMultiplicativeExpression;
  t->variant = NTMultiplicativeExpressionVariants::MultiplicativeExpressionPercUnaryExpression;
  t->multiplicativeExpression = dynamic_cast<TreeMultiplicativeExpression *>((*stack)[n - 1]);
  assert(t->multiplicativeExpression);
  t->unaryExpression = dynamic_cast<TreeUnaryExpression *>((*stack)[n - 2]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::MultiplicativeExpression);
  auto t = new TreeAdditiveExpression;
  t->variant = NTAdditiveExpressionVariants::AdditiveExpressionPlusMultiplicativeExpression;
  t->additiveExpression = dynamic_cast<TreeAdditiveExpression *>((*stack)[n - 1]);
  assert(t->additiveExpression);
  t->multiplicativeExpression = dynamic_cast<TreeMultiplicativeExpression *>((*stack)[n - 2]);
  assert(t->multiplicativeExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// AdditiveExpression -> AdditiveExpression - MultiplicativeExpression 
void parserASTAdditiveExpression_AdditiveExpressionMinusMultiplicativeExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::AdditiveExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::MultiplicativeExpression);
  auto t = new TreeAdditiveExpression;
  t->variant = NTAdditiveExpressionVariants::AdditiveExpressionMinusMultiplicativeExpression;
  t->additiveExpression = dynamic_cast<TreeAdditiveExpression *>((*stack)[n - 1]);
  assert(t->additiveExpression);
  t->multiplicativeExpression = dynamic_cast<TreeMultiplicativeExpression *>((*stack)[n - 2]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::AdditiveExpression);
  auto t = new TreeRelationalExpression;
  t->variant = NTRelationalExpressionVariants::RelationalExpressionLeAdditiveExpression;
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 1]);
  assert(t->relationalExpression);
  t->additiveExpression = dynamic_cast<TreeAdditiveExpression *>((*stack)[n - 2]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression > AdditiveExpression 
void parserASTRelationalExpression_RelationalExpressionGrAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::AdditiveExpression);
  auto t = new TreeRelationalExpression;
  t->variant = NTRelationalExpressionVariants::RelationalExpressionGrAdditiveExpression;
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 1]);
  assert(t->relationalExpression);
  t->additiveExpression = dynamic_cast<TreeAdditiveExpression *>((*stack)[n - 2]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression <= AdditiveExpression 
void parserASTRelationalExpression_RelationalExpressionLeEqAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::AdditiveExpression);
  auto t = new TreeRelationalExpression;
  t->variant = NTRelationalExpressionVariants::RelationalExpressionLeEqAdditiveExpression;
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 1]);
  assert(t->relationalExpression);
  t->additiveExpression = dynamic_cast<TreeAdditiveExpression *>((*stack)[n - 2]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression >= AdditiveExpression 
void parserASTRelationalExpression_RelationalExpressionGrEqAdditiveExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::AdditiveExpression);
  auto t = new TreeRelationalExpression;
  t->variant = NTRelationalExpressionVariants::RelationalExpressionGrEqAdditiveExpression;
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 1]);
  assert(t->relationalExpression);
  t->additiveExpression = dynamic_cast<TreeAdditiveExpression *>((*stack)[n - 2]);
  assert(t->additiveExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// RelationalExpression -> RelationalExpression instanceof ReferenceType 
void parserASTRelationalExpression_RelationalExpressioninstanceofReferenceType(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::RelationalExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::ReferenceType);
  auto t = new TreeRelationalExpression;
  t->variant = NTRelationalExpressionVariants::RelationalExpressioninstanceofReferenceType;
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 1]);
  assert(t->relationalExpression);
  t->referenceType = dynamic_cast<TreeReferenceType *>((*stack)[n - 2]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::EqualityExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  auto t = new TreeEqualityExpression;
  t->variant = NTEqualityExpressionVariants::EqualityExpressionEqEqRelationalExpression;
  t->equalityExpression = dynamic_cast<TreeEqualityExpression *>((*stack)[n - 1]);
  assert(t->equalityExpression);
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 2]);
  assert(t->relationalExpression);
  stack->pop_back();
  stack->pop_back();
  stack->push_back(t);
}

// EqualityExpression -> EqualityExpression != RelationalExpression 
void parserASTEqualityExpression_EqualityExpressionBangEqRelationalExpression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 2);
  assert((*stack)[n - 1]->type == NonTerminalType::EqualityExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::RelationalExpression);
  auto t = new TreeEqualityExpression;
  t->variant = NTEqualityExpressionVariants::EqualityExpressionBangEqRelationalExpression;
  t->equalityExpression = dynamic_cast<TreeEqualityExpression *>((*stack)[n - 1]);
  assert(t->equalityExpression);
  t->relationalExpression = dynamic_cast<TreeRelationalExpression *>((*stack)[n - 2]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::ConditionalAndExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::EqualityExpression);
  auto t = new TreeConditionalAndExpression;
  t->variant = NTConditionalAndExpressionVariants::ConditionalAndExpressionAmpAmpEqualityExpression;
  t->conditionalAndExpression = dynamic_cast<TreeConditionalAndExpression *>((*stack)[n - 1]);
  assert(t->conditionalAndExpression);
  t->equalityExpression = dynamic_cast<TreeEqualityExpression *>((*stack)[n - 2]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::ConditionalOrExpression);
  assert((*stack)[n - 2]->type == NonTerminalType::ConditionalAndExpression);
  auto t = new TreeConditionalOrExpression;
  t->variant = NTConditionalOrExpressionVariants::ConditionalOrExpressionOrOrConditionalAndExpression;
  t->conditionalOrExpression = dynamic_cast<TreeConditionalOrExpression *>((*stack)[n - 1]);
  assert(t->conditionalOrExpression);
  t->conditionalAndExpression = dynamic_cast<TreeConditionalAndExpression *>((*stack)[n - 2]);
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
  assert((*stack)[n - 1]->type == NonTerminalType::LeftHandSide);
  assert((*stack)[n - 2]->type == NonTerminalType::AssignmentExpression);
  auto t = new TreeAssignment;
  t->variant = NTAssignmentVariants::LeftHandSideEqAssignmentExpression;
  t->leftHandSide = dynamic_cast<TreeLeftHandSide *>((*stack)[n - 1]);
  assert(t->leftHandSide);
  t->assignmentExpression = dynamic_cast<TreeAssignmentExpression *>((*stack)[n - 2]);
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
  t->variant = NTExpressionVariants::AssignmentExpression;
  t->assignmentExpression = dynamic_cast<TreeAssignmentExpression *>((*stack)[n - 1]);
  assert(t->assignmentExpression);
  stack->pop_back();
  stack->push_back(t);
}

// ConstantExpression -> Expression 
void parserASTConstantExpression_Expression(vector<Tree *> *stack) {
  int n = stack->size();
  assert(n >= 1);
  assert((*stack)[n - 1]->type == NonTerminalType::Expression);
  auto t = new TreeConstantExpression;
  t->variant = NTConstantExpressionVariants::Expression;
  t->expression = dynamic_cast<TreeExpression *>((*stack)[n - 1]);
  assert(t->expression);
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
    parserASTPrimitiveType_NumericType, 
    parserASTPrimitiveType_boolean, 
    parserASTNumericType_IntegralType, 
    parserASTIntegralType_byte, 
    parserASTIntegralType_Short, 
    parserASTIntegralType_Int, 
    parserASTIntegralType_Char, 
    parserASTReferenceType_ClassOrInterfaceType, 
    parserASTReferenceType_ArrayType, 
    parserASTClassOrInterfaceType_Name, 
    parserASTClassType_ClassOrInterfaceType, 
    parserASTInterfaceType_ClassOrInterfaceType, 
    parserASTArrayType_PrimitiveTypeLSBrRSBr, 
    parserASTArrayType_NameLSBrRSBr, 
    parserASTArrayType_ArrayTypeLSBrRSBr, 
    parserASTName_SimpleName, 
    parserASTName_QualifiedName, 
    parserASTSimpleName_Identifier, 
    parserASTQualifiedName_NameDotIdentifier, 
    parserASTCompilationUnit_, 
    parserASTCompilationUnit_PackageDeclaration, 
    parserASTCompilationUnit_ImportDeclarations, 
    parserASTCompilationUnit_PackageDeclarationImportDeclarations, 
    parserASTCompilationUnit_TypeDeclarations, 
    parserASTCompilationUnit_PackageDeclarationTypeDeclarations, 
    parserASTCompilationUnit_ImportDeclarationsTypeDeclarations, 
    parserASTCompilationUnit_PackageDeclarationImportDeclarationsTypeDeclarations, 
    parserASTImportDeclarations_ImportDeclaration, 
    parserASTImportDeclarations_ImportDeclarationsImportDeclaration, 
    parserASTTypeDeclarations_TypeDeclaration, 
    parserASTTypeDeclarations_TypeDeclarationsTypeDeclaration, 
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
    parserASTClassDeclaration_ClassIdentifierSuperClassBody, 
    parserASTClassDeclaration_ModifiersClassIdentifierSuperClassBody, 
    parserASTClassDeclaration_ClassIdentifierInterfacesClassBody, 
    parserASTClassDeclaration_ModifiersClassIdentifierInterfacesClassBody, 
    parserASTClassDeclaration_ClassIdentifierSuperInterfacesClassBody, 
    parserASTClassDeclaration_ModifiersClassIdentifierSuperInterfacesClassBody, 
    parserASTSuper_extendsClassType, 
    parserASTInterfaces_implementsInterfaceTypeList, 
    parserASTInterfaceTypeList_InterfaceType, 
    parserASTInterfaceTypeList_InterfaceTypeListComInterfaceType, 
    parserASTClassBody_LCBrRCBr, 
    parserASTClassBody_LCBrClassBodyDeclarationsRCBr, 
    parserASTClassBodyDeclarations_ClassBodyDeclaration, 
    parserASTClassBodyDeclarations_ClassBodyDeclarationsClassBodyDeclaration, 
    parserASTClassBodyDeclaration_ClassMemberDeclaration, 
    parserASTClassBodyDeclaration_StaticInitializer, 
    parserASTClassBodyDeclaration_ConstructorDeclaration, 
    parserASTClassMemberDeclaration_FieldDeclaration, 
    parserASTClassMemberDeclaration_MethodDeclaration, 
    parserASTFieldDeclaration_TypeVariableDeclaratorSCol, 
    parserASTFieldDeclaration_ModifiersTypeVariableDeclaratorSCol, 
    parserASTVariableDeclarator_VariableDeclaratorId, 
    parserASTVariableDeclarator_VariableDeclaratorIdEqVariableInitializer, 
    parserASTVariableDeclaratorId_Identifier, 
    parserASTVariableDeclaratorId_VariableDeclaratorIdLSBrRSBr, 
    parserASTVariableInitializer_Expression, 
    parserASTVariableInitializer_ArrayInitializer, 
    parserASTMethodDeclaration_MethodHeaderMethodBody, 
    parserASTMethodHeader_TypeMethodDeclarator, 
    parserASTMethodHeader_ModifiersTypeMethodDeclarator, 
    parserASTMethodHeader_VoidMethodDeclarator, 
    parserASTMethodHeader_ModifiersVoidMethodDeclarator, 
    parserASTMethodDeclarator_IdentifierLParRPar, 
    parserASTMethodDeclarator_IdentifierLParFormalParameterListRPar, 
    parserASTMethodDeclarator_MethodDeclaratorLSBrRSBr, 
    parserASTFormalParameterList_FormalParameter, 
    parserASTFormalParameterList_FormalParameterListComFormalParameter, 
    parserASTFormalParameter_TypeVariableDeclaratorId, 
    parserASTClassTypeList_ClassType, 
    parserASTClassTypeList_ClassTypeListComClassType, 
    parserASTMethodBody_Block, 
    parserASTMethodBody_SCol, 
    parserASTStaticInitializer_StaticBlock, 
    parserASTConstructorDeclaration_ConstructorDeclaratorConstructorBody, 
    parserASTConstructorDeclaration_ModifiersConstructorDeclaratorConstructorBody, 
    parserASTConstructorDeclarator_SimpleNameLParRPar, 
    parserASTConstructorDeclarator_SimpleNameLParFormalParameterListRPar, 
    parserASTConstructorBody_LCBrRCBr, 
    parserASTConstructorBody_LCBrBlockStatementsRCBr, 
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
    parserASTInterfaceMemberDeclaration_ConstantDeclaration, 
    parserASTInterfaceMemberDeclaration_AbstractMethodDeclaration, 
    parserASTConstantDeclaration_FieldDeclaration, 
    parserASTAbstractMethodDeclaration_MethodHeaderSCol, 
    parserASTArrayInitializer_LCBrRCBr, 
    parserASTArrayInitializer_LCBrVariableInitializersRCBr, 
    parserASTArrayInitializer_LCBrComRCBr, 
    parserASTArrayInitializer_LCBrVariableInitializersComRCBr, 
    parserASTVariableInitializers_VariableInitializer, 
    parserASTVariableInitializers_VariableInitializersComVariableInitializer, 
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
    parserASTPrimaryNoNewArray_This, 
    parserASTPrimaryNoNewArray_LParExpressionRPar, 
    parserASTPrimaryNoNewArray_ClassInstanceCreationExpression, 
    parserASTPrimaryNoNewArray_FieldAccess, 
    parserASTPrimaryNoNewArray_MethodInvocation, 
    parserASTPrimaryNoNewArray_ArrayAccess, 
    parserASTClassInstanceCreationExpression_NewClassTypeLParRPar, 
    parserASTClassInstanceCreationExpression_NewClassTypeLParArgumentListRPar, 
    parserASTArgumentList_Expression, 
    parserASTArgumentList_ArgumentListComExpression, 
    parserASTArrayCreationExpression_NewPrimitiveTypeDimExprs, 
    parserASTArrayCreationExpression_NewPrimitiveTypeDimExprsDims, 
    parserASTArrayCreationExpression_NewClassOrInterfaceTypeDimExprs, 
    parserASTArrayCreationExpression_NewClassOrInterfaceTypeDimExprsDims, 
    parserASTDimExprs_DimExpr, 
    parserASTDimExprs_DimExprsDimExpr, 
    parserASTDimExpr_LSBrExpressionRSBr, 
    parserASTDims_LSBrRSBr, 
    parserASTDims_DimsLSBrRSBr, 
    parserASTFieldAccess_PrimaryDotIdentifier, 
    parserASTMethodInvocation_NameLParRPar, 
    parserASTMethodInvocation_NameLParArgumentListRPar, 
    parserASTMethodInvocation_PrimaryDotIdentifierLParRPar, 
    parserASTMethodInvocation_PrimaryDotIdentifierLParArgumentListRPar, 
    parserASTArrayAccess_NameLSBrExpressionRSBr, 
    parserASTArrayAccess_PrimaryNoNewArrayLSBrExpressionRSBr, 
    parserASTPostfixExpression_Primary, 
    parserASTPostfixExpression_Name, 
    parserASTUnaryExpression_MinusUnaryExpression, 
    parserASTUnaryExpression_UnaryExpressionNotPlusMinus, 
    parserASTUnaryExpressionNotPlusMinus_PostfixExpression, 
    parserASTUnaryExpressionNotPlusMinus_TilUnaryExpression, 
    parserASTUnaryExpressionNotPlusMinus_BangUnaryExpression, 
    parserASTUnaryExpressionNotPlusMinus_CastExpression, 
    parserASTCastExpression_LParPrimitiveTypeRParUnaryExpression, 
    parserASTCastExpression_LParPrimitiveTypeDimsRParUnaryExpression, 
    parserASTCastExpression_LParExpressionRParUnaryExpressionNotPlusMinus, 
    parserASTCastExpression_LParNameDimsRParUnaryExpressionNotPlusMinus, 
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
    parserASTConstantExpression_Expression, 
  };
  table[ruleID](stack);
}

} // namespace Parse 
