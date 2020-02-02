#pragma once
#include "parserASTBase.h"
namespace Parse { 
enum class NTExpressionVariants {
  AssignmentExpression,  // AssignmentExpression 
  Max,
};

struct TreeExpression: public Tree {
  enum NTExpressionVariants variant;
  TreeAssignmentExpression* assignmentExpression;

  TreeExpression(): Tree(NonTerminalType::Expression), variant(NTExpressionVariants::Max), assignmentExpression(nullptr) {

  }
};

enum class NTAssignmentVariants {
  LeftHandSideEqAssignmentExpression,  // LeftHandSide = AssignmentExpression 
  Max,
};

struct TreeAssignment: public Tree {
  enum NTAssignmentVariants variant;
  TreeAssignmentExpression* assignmentExpression;
  TreeLeftHandSide* leftHandSide;

  TreeAssignment(): Tree(NonTerminalType::Assignment), variant(NTAssignmentVariants::Max), assignmentExpression(nullptr) , leftHandSide(nullptr) {

  }
};

enum class NTConditionalOrExpressionVariants {
  ConditionalAndExpression,  // ConditionalAndExpression 
  ConditionalOrExpressionOrOrConditionalAndExpression,  // ConditionalOrExpression || ConditionalAndExpression 
  Max,
};

struct TreeConditionalOrExpression: public Tree {
  enum NTConditionalOrExpressionVariants variant;
  TreeConditionalOrExpression* conditionalOrExpression;
  TreeConditionalAndExpression* conditionalAndExpression;

  TreeConditionalOrExpression(): Tree(NonTerminalType::ConditionalOrExpression), variant(NTConditionalOrExpressionVariants::Max), conditionalOrExpression(nullptr) , conditionalAndExpression(nullptr) {

  }
};

enum class NTEqualityExpressionVariants {
  RelationalExpression,  // RelationalExpression 
  EqualityExpressionEqEqRelationalExpression,  // EqualityExpression == RelationalExpression 
  EqualityExpressionBangEqRelationalExpression,  // EqualityExpression != RelationalExpression 
  Max,
};

struct TreeEqualityExpression: public Tree {
  enum NTEqualityExpressionVariants variant;
  TreeEqualityExpression* equalityExpression;
  TreeRelationalExpression* relationalExpression;

  TreeEqualityExpression(): Tree(NonTerminalType::EqualityExpression), variant(NTEqualityExpressionVariants::Max), equalityExpression(nullptr) , relationalExpression(nullptr) {

  }
};

enum class NTAdditiveExpressionVariants {
  MultiplicativeExpression,  // MultiplicativeExpression 
  AdditiveExpressionPlusMultiplicativeExpression,  // AdditiveExpression + MultiplicativeExpression 
  AdditiveExpressionMinusMultiplicativeExpression,  // AdditiveExpression - MultiplicativeExpression 
  Max,
};

struct TreeAdditiveExpression: public Tree {
  enum NTAdditiveExpressionVariants variant;
  TreeAdditiveExpression* additiveExpression;
  TreeMultiplicativeExpression* multiplicativeExpression;

  TreeAdditiveExpression(): Tree(NonTerminalType::AdditiveExpression), variant(NTAdditiveExpressionVariants::Max), additiveExpression(nullptr) , multiplicativeExpression(nullptr) {

  }
};

enum class NTMultiplicativeExpressionVariants {
  UnaryExpression,  // UnaryExpression 
  MultiplicativeExpressionStarUnaryExpression,  // MultiplicativeExpression * UnaryExpression 
  MultiplicativeExpressionRSlashUnaryExpression,  // MultiplicativeExpression / UnaryExpression 
  MultiplicativeExpressionPercUnaryExpression,  // MultiplicativeExpression % UnaryExpression 
  Max,
};

struct TreeMultiplicativeExpression: public Tree {
  enum NTMultiplicativeExpressionVariants variant;
  TreeMultiplicativeExpression* multiplicativeExpression;
  TreeUnaryExpression* unaryExpression;

  TreeMultiplicativeExpression(): Tree(NonTerminalType::MultiplicativeExpression), variant(NTMultiplicativeExpressionVariants::Max), multiplicativeExpression(nullptr) , unaryExpression(nullptr) {

  }
};

enum class NTMethodDeclaratorVariants {
  IdentifierLParRPar,  // Identifier ( ) 
  IdentifierLParFormalParameterListRPar,  // Identifier ( FormalParameterList ) 
  MethodDeclaratorLSBrRSBr,  // MethodDeclarator [ ] 
  Max,
};

struct TreeMethodDeclarator: public Tree {
  enum NTMethodDeclaratorVariants variant;
  TreeMethodDeclarator* methodDeclarator;
  TreeIdentifier* identifier;
  TreeFormalParameterList* formalParameterList;

  TreeMethodDeclarator(): Tree(NonTerminalType::MethodDeclarator), variant(NTMethodDeclaratorVariants::Max), methodDeclarator(nullptr) , identifier(nullptr) , formalParameterList(nullptr) {

  }
};

enum class NTVariableInitializerVariants {
  Expression,  // Expression 
  ArrayInitializer,  // ArrayInitializer 
  Max,
};

struct TreeVariableInitializer: public Tree {
  enum NTVariableInitializerVariants variant;
  TreeArrayInitializer* arrayInitializer;
  TreeExpression* expression;

  TreeVariableInitializer(): Tree(NonTerminalType::VariableInitializer), variant(NTVariableInitializerVariants::Max), arrayInitializer(nullptr) , expression(nullptr) {

  }
};

enum class NTFieldDeclarationVariants {
  TypeVariableDeclaratorSCol,  // Type VariableDeclarator ; 
  ModifiersTypeVariableDeclaratorSCol,  // Modifiers Type VariableDeclarator ; 
  Max,
};

struct TreeFieldDeclaration: public Tree {
  enum NTFieldDeclarationVariants variant;
  TreeType* type;
  TreeModifiers* modifiers;
  TreeVariableDeclarator* variableDeclarator;

  TreeFieldDeclaration(): Tree(NonTerminalType::FieldDeclaration), variant(NTFieldDeclarationVariants::Max), type(nullptr) , modifiers(nullptr) , variableDeclarator(nullptr) {

  }
};

enum class NTInterfacesVariants {
  implementsInterfaceTypeList,  // implements InterfaceTypeList 
  Max,
};

struct TreeInterfaces: public Tree {
  enum NTInterfacesVariants variant;
  TreeInterfaceTypeList* interfaceTypeList;

  TreeInterfaces(): Tree(NonTerminalType::Interfaces), variant(NTInterfacesVariants::Max), interfaceTypeList(nullptr) {

  }
};

enum class NTClassBodyDeclarationsVariants {
  ClassBodyDeclaration,  // ClassBodyDeclaration 
  ClassBodyDeclarationsClassBodyDeclaration,  // ClassBodyDeclarations ClassBodyDeclaration 
  Max,
};

struct TreeClassBodyDeclarations: public Tree {
  enum NTClassBodyDeclarationsVariants variant;
  TreeClassBodyDeclarations* classBodyDeclarations;
  TreeClassBodyDeclaration* classBodyDeclaration;

  TreeClassBodyDeclarations(): Tree(NonTerminalType::ClassBodyDeclarations), variant(NTClassBodyDeclarationsVariants::Max), classBodyDeclarations(nullptr) , classBodyDeclaration(nullptr) {

  }
};

enum class NTClassDeclarationVariants {
  ClassIdentifierClassBody,  // class Identifier ClassBody 
  ModifiersClassIdentifierClassBody,  // Modifiers class Identifier ClassBody 
  ClassIdentifierSuperClassBody,  // class Identifier Super ClassBody 
  ModifiersClassIdentifierSuperClassBody,  // Modifiers class Identifier Super ClassBody 
  ClassIdentifierInterfacesClassBody,  // class Identifier Interfaces ClassBody 
  ModifiersClassIdentifierInterfacesClassBody,  // Modifiers class Identifier Interfaces ClassBody 
  ClassIdentifierSuperInterfacesClassBody,  // class Identifier Super Interfaces ClassBody 
  ModifiersClassIdentifierSuperInterfacesClassBody,  // Modifiers class Identifier Super Interfaces ClassBody 
  Max,
};

struct TreeClassDeclaration: public Tree {
  enum NTClassDeclarationVariants variant;
  TreeInterfaces* interfaces;
  TreeSuper* super;
  TreeModifiers* modifiers;
  TreeIdentifier* identifier;
  TreeClassBody* classBody;

  TreeClassDeclaration(): Tree(NonTerminalType::ClassDeclaration), variant(NTClassDeclarationVariants::Max), interfaces(nullptr) , super(nullptr) , modifiers(nullptr) , identifier(nullptr) , classBody(nullptr) {

  }
};

enum class NTConstantExpressionVariants {
  Expression,  // Expression 
  Max,
};

struct TreeConstantExpression: public Tree {
  enum NTConstantExpressionVariants variant;
  TreeExpression* expression;

  TreeConstantExpression(): Tree(NonTerminalType::ConstantExpression), variant(NTConstantExpressionVariants::Max), expression(nullptr) {

  }
};

enum class NTClassInstanceCreationExpressionVariants {
  NewClassTypeLParRPar,  // new ClassType ( ) 
  NewClassTypeLParArgumentListRPar,  // new ClassType ( ArgumentList ) 
  Max,
};

struct TreeClassInstanceCreationExpression: public Tree {
  enum NTClassInstanceCreationExpressionVariants variant;
  TreeArgumentList* argumentList;
  TreeClassType* classType;

  TreeClassInstanceCreationExpression(): Tree(NonTerminalType::ClassInstanceCreationExpression), variant(NTClassInstanceCreationExpressionVariants::Max), argumentList(nullptr) , classType(nullptr) {

  }
};

enum class NTModifierVariants {
  Public,  // public 
  Protected,  // protected 
  Static,  // static 
  abstract,  // abstract 
  final,  // final 
  native,  // native 
  Max,
};

struct TreeModifier: public Tree {
  enum NTModifierVariants variant;

  TreeModifier(): Tree(NonTerminalType::Modifier), variant(NTModifierVariants::Max){

  }
};

enum class NTConstructorDeclarationVariants {
  ConstructorDeclaratorConstructorBody,  // ConstructorDeclarator ConstructorBody 
  ModifiersConstructorDeclaratorConstructorBody,  // Modifiers ConstructorDeclarator ConstructorBody 
  Max,
};

struct TreeConstructorDeclaration: public Tree {
  enum NTConstructorDeclarationVariants variant;
  TreeModifiers* modifiers;
  TreeConstructorDeclarator* constructorDeclarator;
  TreeConstructorBody* constructorBody;

  TreeConstructorDeclaration(): Tree(NonTerminalType::ConstructorDeclaration), variant(NTConstructorDeclarationVariants::Max), modifiers(nullptr) , constructorDeclarator(nullptr) , constructorBody(nullptr) {

  }
};

enum class NTClassBodyDeclarationVariants {
  ClassMemberDeclaration,  // ClassMemberDeclaration 
  StaticInitializer,  // StaticInitializer 
  ConstructorDeclaration,  // ConstructorDeclaration 
  Max,
};

struct TreeClassBodyDeclaration: public Tree {
  enum NTClassBodyDeclarationVariants variant;
  TreeConstructorDeclaration* constructorDeclaration;
  TreeClassMemberDeclaration* classMemberDeclaration;
  TreeStaticInitializer* staticInitializer;

  TreeClassBodyDeclaration(): Tree(NonTerminalType::ClassBodyDeclaration), variant(NTClassBodyDeclarationVariants::Max), constructorDeclaration(nullptr) , classMemberDeclaration(nullptr) , staticInitializer(nullptr) {

  }
};

enum class NTCastExpressionVariants {
  LParPrimitiveTypeRParUnaryExpression,  // ( PrimitiveType ) UnaryExpression 
  LParPrimitiveTypeDimsRParUnaryExpression,  // ( PrimitiveType Dims ) UnaryExpression 
  LParExpressionRParUnaryExpressionNotPlusMinus,  // ( Expression ) UnaryExpressionNotPlusMinus 
  LParNameDimsRParUnaryExpressionNotPlusMinus,  // ( Name Dims ) UnaryExpressionNotPlusMinus 
  Max,
};

struct TreeCastExpression: public Tree {
  enum NTCastExpressionVariants variant;
  TreeUnaryExpression* unaryExpression;
  TreeName* name;
  TreePrimitiveType* primitiveType;
  TreeDims* dims;
  TreeUnaryExpressionNotPlusMinus* unaryExpressionNotPlusMinus;
  TreeExpression* expression;

  TreeCastExpression(): Tree(NonTerminalType::CastExpression), variant(NTCastExpressionVariants::Max), unaryExpression(nullptr) , name(nullptr) , primitiveType(nullptr) , dims(nullptr) , unaryExpressionNotPlusMinus(nullptr) , expression(nullptr) {

  }
};

enum class NTClassMemberDeclarationVariants {
  FieldDeclaration,  // FieldDeclaration 
  MethodDeclaration,  // MethodDeclaration 
  Max,
};

struct TreeClassMemberDeclaration: public Tree {
  enum NTClassMemberDeclarationVariants variant;
  TreeMethodDeclaration* methodDeclaration;
  TreeFieldDeclaration* fieldDeclaration;

  TreeClassMemberDeclaration(): Tree(NonTerminalType::ClassMemberDeclaration), variant(NTClassMemberDeclarationVariants::Max), methodDeclaration(nullptr) , fieldDeclaration(nullptr) {

  }
};

enum class NTTypeDeclarationVariants {
  ClassDeclaration,  // ClassDeclaration 
  InterfaceDeclaration,  // InterfaceDeclaration 
  SCol,  // ; 
  Max,
};

struct TreeTypeDeclaration: public Tree {
  enum NTTypeDeclarationVariants variant;
  TreeInterfaceDeclaration* interfaceDeclaration;
  TreeClassDeclaration* classDeclaration;

  TreeTypeDeclaration(): Tree(NonTerminalType::TypeDeclaration), variant(NTTypeDeclarationVariants::Max), interfaceDeclaration(nullptr) , classDeclaration(nullptr) {

  }
};

enum class NTMethodHeaderVariants {
  TypeMethodDeclarator,  // Type MethodDeclarator 
  ModifiersTypeMethodDeclarator,  // Modifiers Type MethodDeclarator 
  VoidMethodDeclarator,  // void MethodDeclarator 
  ModifiersVoidMethodDeclarator,  // Modifiers void MethodDeclarator 
  Max,
};

struct TreeMethodHeader: public Tree {
  enum NTMethodHeaderVariants variant;
  TreeModifiers* modifiers;
  TreeType* type;
  TreeMethodDeclarator* methodDeclarator;

  TreeMethodHeader(): Tree(NonTerminalType::MethodHeader), variant(NTMethodHeaderVariants::Max), modifiers(nullptr) , type(nullptr) , methodDeclarator(nullptr) {

  }
};

enum class NTModifiersVariants {
  Modifier,  // Modifier 
  ModifiersModifier,  // Modifiers Modifier 
  Max,
};

struct TreeModifiers: public Tree {
  enum NTModifiersVariants variant;
  TreeModifiers* modifiers;
  TreeModifier* modifier;

  TreeModifiers(): Tree(NonTerminalType::Modifiers), variant(NTModifiersVariants::Max), modifiers(nullptr) , modifier(nullptr) {

  }
};

enum class NTSingleTypeImportDeclarationVariants {
  importNameSCol,  // import Name ; 
  Max,
};

struct TreeSingleTypeImportDeclaration: public Tree {
  enum NTSingleTypeImportDeclarationVariants variant;
  TreeName* name;

  TreeSingleTypeImportDeclaration(): Tree(NonTerminalType::SingleTypeImportDeclaration), variant(NTSingleTypeImportDeclarationVariants::Max), name(nullptr) {

  }
};

enum class NTFormalParameterListVariants {
  FormalParameter,  // FormalParameter 
  FormalParameterListComFormalParameter,  // FormalParameterList , FormalParameter 
  Max,
};

struct TreeFormalParameterList: public Tree {
  enum NTFormalParameterListVariants variant;
  TreeFormalParameterList* formalParameterList;
  TreeFormalParameter* formalParameter;

  TreeFormalParameterList(): Tree(NonTerminalType::FormalParameterList), variant(NTFormalParameterListVariants::Max), formalParameterList(nullptr) , formalParameter(nullptr) {

  }
};

enum class NTMethodDeclarationVariants {
  MethodHeaderMethodBody,  // MethodHeader MethodBody 
  Max,
};

struct TreeMethodDeclaration: public Tree {
  enum NTMethodDeclarationVariants variant;
  TreeMethodBody* methodBody;
  TreeMethodHeader* methodHeader;

  TreeMethodDeclaration(): Tree(NonTerminalType::MethodDeclaration), variant(NTMethodDeclarationVariants::Max), methodBody(nullptr) , methodHeader(nullptr) {

  }
};

enum class NTPackageDeclarationVariants {
  packageNameSCol,  // package Name ; 
  Max,
};

struct TreePackageDeclaration: public Tree {
  enum NTPackageDeclarationVariants variant;
  TreeName* name;

  TreePackageDeclaration(): Tree(NonTerminalType::PackageDeclaration), variant(NTPackageDeclarationVariants::Max), name(nullptr) {

  }
};

enum class NTVariableDeclaratorVariants {
  VariableDeclaratorId,  // VariableDeclaratorId 
  VariableDeclaratorIdEqVariableInitializer,  // VariableDeclaratorId = VariableInitializer 
  Max,
};

struct TreeVariableDeclarator: public Tree {
  enum NTVariableDeclaratorVariants variant;
  TreeVariableInitializer* variableInitializer;
  TreeVariableDeclaratorId* variableDeclaratorId;

  TreeVariableDeclarator(): Tree(NonTerminalType::VariableDeclarator), variant(NTVariableDeclaratorVariants::Max), variableInitializer(nullptr) , variableDeclaratorId(nullptr) {

  }
};

enum class NTDimExprVariants {
  LSBrExpressionRSBr,  // [ Expression ] 
  Max,
};

struct TreeDimExpr: public Tree {
  enum NTDimExprVariants variant;
  TreeExpression* expression;

  TreeDimExpr(): Tree(NonTerminalType::DimExpr), variant(NTDimExprVariants::Max), expression(nullptr) {

  }
};

enum class NTAssignmentExpressionVariants {
  ConditionalOrExpression,  // ConditionalOrExpression 
  Assignment,  // Assignment 
  Max,
};

struct TreeAssignmentExpression: public Tree {
  enum NTAssignmentExpressionVariants variant;
  TreeAssignment* assignment;
  TreeConditionalOrExpression* conditionalOrExpression;

  TreeAssignmentExpression(): Tree(NonTerminalType::AssignmentExpression), variant(NTAssignmentExpressionVariants::Max), assignment(nullptr) , conditionalOrExpression(nullptr) {

  }
};

enum class NTRelationalExpressionVariants {
  AdditiveExpression,  // AdditiveExpression 
  RelationalExpressionLeAdditiveExpression,  // RelationalExpression < AdditiveExpression 
  RelationalExpressionGrAdditiveExpression,  // RelationalExpression > AdditiveExpression 
  RelationalExpressionLeEqAdditiveExpression,  // RelationalExpression <= AdditiveExpression 
  RelationalExpressionGrEqAdditiveExpression,  // RelationalExpression >= AdditiveExpression 
  RelationalExpressioninstanceofReferenceType,  // RelationalExpression instanceof ReferenceType 
  Max,
};

struct TreeRelationalExpression: public Tree {
  enum NTRelationalExpressionVariants variant;
  TreeReferenceType* referenceType;
  TreeAdditiveExpression* additiveExpression;
  TreeRelationalExpression* relationalExpression;

  TreeRelationalExpression(): Tree(NonTerminalType::RelationalExpression), variant(NTRelationalExpressionVariants::Max), referenceType(nullptr) , additiveExpression(nullptr) , relationalExpression(nullptr) {

  }
};

enum class NTClassBodyVariants {
  LCBrRCBr,  // { } 
  LCBrClassBodyDeclarationsRCBr,  // { ClassBodyDeclarations } 
  Max,
};

struct TreeClassBody: public Tree {
  enum NTClassBodyVariants variant;
  TreeClassBodyDeclarations* classBodyDeclarations;

  TreeClassBody(): Tree(NonTerminalType::ClassBody), variant(NTClassBodyVariants::Max), classBodyDeclarations(nullptr) {

  }
};

enum class NTNameVariants {
  SimpleName,  // SimpleName 
  QualifiedName,  // QualifiedName 
  Max,
};

struct TreeName: public Tree {
  enum NTNameVariants variant;
  TreeQualifiedName* qualifiedName;
  TreeSimpleName* simpleName;

  TreeName(): Tree(NonTerminalType::Name), variant(NTNameVariants::Max), qualifiedName(nullptr) , simpleName(nullptr) {

  }
};

enum class NTArrayCreationExpressionVariants {
  NewPrimitiveTypeDimExprs,  // new PrimitiveType DimExprs 
  NewPrimitiveTypeDimExprsDims,  // new PrimitiveType DimExprs Dims 
  NewClassOrInterfaceTypeDimExprs,  // new ClassOrInterfaceType DimExprs 
  NewClassOrInterfaceTypeDimExprsDims,  // new ClassOrInterfaceType DimExprs Dims 
  Max,
};

struct TreeArrayCreationExpression: public Tree {
  enum NTArrayCreationExpressionVariants variant;
  TreeClassOrInterfaceType* classOrInterfaceType;
  TreeDims* dims;
  TreePrimitiveType* primitiveType;
  TreeDimExprs* dimExprs;

  TreeArrayCreationExpression(): Tree(NonTerminalType::ArrayCreationExpression), variant(NTArrayCreationExpressionVariants::Max), classOrInterfaceType(nullptr) , dims(nullptr) , primitiveType(nullptr) , dimExprs(nullptr) {

  }
};

enum class NTClassOrInterfaceTypeVariants {
  Name,  // Name 
  Max,
};

struct TreeClassOrInterfaceType: public Tree {
  enum NTClassOrInterfaceTypeVariants variant;
  TreeName* name;

  TreeClassOrInterfaceType(): Tree(NonTerminalType::ClassOrInterfaceType), variant(NTClassOrInterfaceTypeVariants::Max), name(nullptr) {

  }
};

enum class NTTypeVariants {
  PrimitiveType,  // PrimitiveType 
  ReferenceType,  // ReferenceType 
  Max,
};

struct TreeType: public Tree {
  enum NTTypeVariants variant;
  TreeReferenceType* referenceType;
  TreePrimitiveType* primitiveType;

  TreeType(): Tree(NonTerminalType::Type), variant(NTTypeVariants::Max), referenceType(nullptr) , primitiveType(nullptr) {

  }
};

enum class NTClassTypeListVariants {
  ClassType,  // ClassType 
  ClassTypeListComClassType,  // ClassTypeList , ClassType 
  Max,
};

struct TreeClassTypeList: public Tree {
  enum NTClassTypeListVariants variant;
  TreeClassTypeList* classTypeList;
  TreeClassType* classType;

  TreeClassTypeList(): Tree(NonTerminalType::ClassTypeList), variant(NTClassTypeListVariants::Max), classTypeList(nullptr) , classType(nullptr) {

  }
};

enum class NTLiteralVariants {
  IntegerLiteral,  // IntegerLiteral 
  BooleanLiteral,  // BooleanLiteral 
  CharacterLiteral,  // CharacterLiteral 
  StringLiteral,  // StringLiteral 
  NullLiteral,  // NullLiteral 
  Max,
};

struct TreeLiteral: public Tree {
  enum NTLiteralVariants variant;
  TreeNullLiteral* nullLiteral;
  TreeCharacterLiteral* characterLiteral;
  TreeIntegerLiteral* integerLiteral;
  TreeStringLiteral* stringLiteral;
  TreeBooleanLiteral* booleanLiteral;

  TreeLiteral(): Tree(NonTerminalType::Literal), variant(NTLiteralVariants::Max), nullLiteral(nullptr) , characterLiteral(nullptr) , integerLiteral(nullptr) , stringLiteral(nullptr) , booleanLiteral(nullptr) {

  }
};

enum class NTInterfaceTypeListVariants {
  InterfaceType,  // InterfaceType 
  InterfaceTypeListComInterfaceType,  // InterfaceTypeList , InterfaceType 
  Max,
};

struct TreeInterfaceTypeList: public Tree {
  enum NTInterfaceTypeListVariants variant;
  TreeInterfaceTypeList* interfaceTypeList;
  TreeInterfaceType* interfaceType;

  TreeInterfaceTypeList(): Tree(NonTerminalType::InterfaceTypeList), variant(NTInterfaceTypeListVariants::Max), interfaceTypeList(nullptr) , interfaceType(nullptr) {

  }
};

enum class NTBooleanLiteralVariants {
  Max,
};

struct TreeBooleanLiteral: public Tree {
  enum NTBooleanLiteralVariants variant;

  TreeBooleanLiteral(): Tree(NonTerminalType::BooleanLiteral), variant(NTBooleanLiteralVariants::Max){

  }
};

enum class NTPrimitiveTypeVariants {
  NumericType,  // NumericType 
  boolean,  // boolean 
  Max,
};

struct TreePrimitiveType: public Tree {
  enum NTPrimitiveTypeVariants variant;
  TreeNumericType* numericType;

  TreePrimitiveType(): Tree(NonTerminalType::PrimitiveType), variant(NTPrimitiveTypeVariants::Max), numericType(nullptr) {

  }
};

enum class NTIdentifierVariants {
  Max,
};

struct TreeIdentifier: public Tree {
  enum NTIdentifierVariants variant;

  TreeIdentifier(): Tree(NonTerminalType::Identifier), variant(NTIdentifierVariants::Max){

  }
};

enum class NTStatementWithoutTrailingSubstatementVariants {
  Block,  // Block 
  EmptyStatement,  // EmptyStatement 
  ExpressionStatement,  // ExpressionStatement 
  ReturnStatement,  // ReturnStatement 
  Max,
};

struct TreeStatementWithoutTrailingSubstatement: public Tree {
  enum NTStatementWithoutTrailingSubstatementVariants variant;
  TreeExpressionStatement* expressionStatement;
  TreeBlock* block;
  TreeReturnStatement* returnStatement;
  TreeEmptyStatement* emptyStatement;

  TreeStatementWithoutTrailingSubstatement(): Tree(NonTerminalType::StatementWithoutTrailingSubstatement), variant(NTStatementWithoutTrailingSubstatementVariants::Max), expressionStatement(nullptr) , block(nullptr) , returnStatement(nullptr) , emptyStatement(nullptr) {

  }
};

enum class NTGoalVariants {
  BOFCompilationUnitEof,  // BOF CompilationUnit EOF 
  Max,
};

struct TreeGoal: public Tree {
  enum NTGoalVariants variant;
  TreeCompilationUnit* compilationUnit;

  TreeGoal(): Tree(NonTerminalType::Goal), variant(NTGoalVariants::Max), compilationUnit(nullptr) {

  }
};

enum class NTLeftHandSideVariants {
  Name,  // Name 
  FieldAccess,  // FieldAccess 
  ArrayAccess,  // ArrayAccess 
  Max,
};

struct TreeLeftHandSide: public Tree {
  enum NTLeftHandSideVariants variant;
  TreeName* name;
  TreeArrayAccess* arrayAccess;
  TreeFieldAccess* fieldAccess;

  TreeLeftHandSide(): Tree(NonTerminalType::LeftHandSide), variant(NTLeftHandSideVariants::Max), name(nullptr) , arrayAccess(nullptr) , fieldAccess(nullptr) {

  }
};

enum class NTCompilationUnitVariants {
  PackageDeclaration,  // PackageDeclaration 
  ImportDeclarations,  // ImportDeclarations 
  PackageDeclarationImportDeclarations,  // PackageDeclaration ImportDeclarations 
  TypeDeclarations,  // TypeDeclarations 
  PackageDeclarationTypeDeclarations,  // PackageDeclaration TypeDeclarations 
  ImportDeclarationsTypeDeclarations,  // ImportDeclarations TypeDeclarations 
  PackageDeclarationImportDeclarationsTypeDeclarations,  // PackageDeclaration ImportDeclarations TypeDeclarations 
  Max,
};

struct TreeCompilationUnit: public Tree {
  enum NTCompilationUnitVariants variant;
  TreeTypeDeclarations* typeDeclarations;
  TreePackageDeclaration* packageDeclaration;
  TreeImportDeclarations* importDeclarations;

  TreeCompilationUnit(): Tree(NonTerminalType::CompilationUnit), variant(NTCompilationUnitVariants::Max), typeDeclarations(nullptr) , packageDeclaration(nullptr) , importDeclarations(nullptr) {

  }
};

enum class NTCharacterLiteralVariants {
  Max,
};

struct TreeCharacterLiteral: public Tree {
  enum NTCharacterLiteralVariants variant;

  TreeCharacterLiteral(): Tree(NonTerminalType::CharacterLiteral), variant(NTCharacterLiteralVariants::Max){

  }
};

enum class NTInterfaceTypeVariants {
  ClassOrInterfaceType,  // ClassOrInterfaceType 
  Max,
};

struct TreeInterfaceType: public Tree {
  enum NTInterfaceTypeVariants variant;
  TreeClassOrInterfaceType* classOrInterfaceType;

  TreeInterfaceType(): Tree(NonTerminalType::InterfaceType), variant(NTInterfaceTypeVariants::Max), classOrInterfaceType(nullptr) {

  }
};

enum class NTReferenceTypeVariants {
  ClassOrInterfaceType,  // ClassOrInterfaceType 
  ArrayType,  // ArrayType 
  Max,
};

struct TreeReferenceType: public Tree {
  enum NTReferenceTypeVariants variant;
  TreeArrayType* arrayType;
  TreeClassOrInterfaceType* classOrInterfaceType;

  TreeReferenceType(): Tree(NonTerminalType::ReferenceType), variant(NTReferenceTypeVariants::Max), arrayType(nullptr) , classOrInterfaceType(nullptr) {

  }
};

enum class NTImportDeclarationsVariants {
  ImportDeclaration,  // ImportDeclaration 
  ImportDeclarationsImportDeclaration,  // ImportDeclarations ImportDeclaration 
  Max,
};

struct TreeImportDeclarations: public Tree {
  enum NTImportDeclarationsVariants variant;
  TreeImportDeclarations* importDeclarations;
  TreeImportDeclaration* importDeclaration;

  TreeImportDeclarations(): Tree(NonTerminalType::ImportDeclarations), variant(NTImportDeclarationsVariants::Max), importDeclarations(nullptr) , importDeclaration(nullptr) {

  }
};

enum class NTFormalParameterVariants {
  TypeVariableDeclaratorId,  // Type VariableDeclaratorId 
  Max,
};

struct TreeFormalParameter: public Tree {
  enum NTFormalParameterVariants variant;
  TreeVariableDeclaratorId* variableDeclaratorId;
  TreeType* type;

  TreeFormalParameter(): Tree(NonTerminalType::FormalParameter), variant(NTFormalParameterVariants::Max), variableDeclaratorId(nullptr) , type(nullptr) {

  }
};

enum class NTStatementExpressionVariants {
  Assignment,  // Assignment 
  MethodInvocation,  // MethodInvocation 
  ClassInstanceCreationExpression,  // ClassInstanceCreationExpression 
  Max,
};

struct TreeStatementExpression: public Tree {
  enum NTStatementExpressionVariants variant;
  TreeClassInstanceCreationExpression* classInstanceCreationExpression;
  TreeAssignment* assignment;
  TreeMethodInvocation* methodInvocation;

  TreeStatementExpression(): Tree(NonTerminalType::StatementExpression), variant(NTStatementExpressionVariants::Max), classInstanceCreationExpression(nullptr) , assignment(nullptr) , methodInvocation(nullptr) {

  }
};

enum class NTConstructorBodyVariants {
  LCBrRCBr,  // { } 
  LCBrBlockStatementsRCBr,  // { BlockStatements } 
  Max,
};

struct TreeConstructorBody: public Tree {
  enum NTConstructorBodyVariants variant;
  TreeBlockStatements* blockStatements;

  TreeConstructorBody(): Tree(NonTerminalType::ConstructorBody), variant(NTConstructorBodyVariants::Max), blockStatements(nullptr) {

  }
};

enum class NTLocalVariableDeclarationVariants {
  TypeVariableDeclarator,  // Type VariableDeclarator 
  Max,
};

struct TreeLocalVariableDeclaration: public Tree {
  enum NTLocalVariableDeclarationVariants variant;
  TreeVariableDeclarator* variableDeclarator;
  TreeType* type;

  TreeLocalVariableDeclaration(): Tree(NonTerminalType::LocalVariableDeclaration), variant(NTLocalVariableDeclarationVariants::Max), variableDeclarator(nullptr) , type(nullptr) {

  }
};

enum class NTClassTypeVariants {
  ClassOrInterfaceType,  // ClassOrInterfaceType 
  Max,
};

struct TreeClassType: public Tree {
  enum NTClassTypeVariants variant;
  TreeClassOrInterfaceType* classOrInterfaceType;

  TreeClassType(): Tree(NonTerminalType::ClassType), variant(NTClassTypeVariants::Max), classOrInterfaceType(nullptr) {

  }
};

enum class NTArrayTypeVariants {
  PrimitiveTypeLSBrRSBr,  // PrimitiveType [ ] 
  NameLSBrRSBr,  // Name [ ] 
  ArrayTypeLSBrRSBr,  // ArrayType [ ] 
  Max,
};

struct TreeArrayType: public Tree {
  enum NTArrayTypeVariants variant;
  TreeArrayType* arrayType;
  TreePrimitiveType* primitiveType;
  TreeName* name;

  TreeArrayType(): Tree(NonTerminalType::ArrayType), variant(NTArrayTypeVariants::Max), arrayType(nullptr) , primitiveType(nullptr) , name(nullptr) {

  }
};

enum class NTNumericTypeVariants {
  IntegralType,  // IntegralType 
  Max,
};

struct TreeNumericType: public Tree {
  enum NTNumericTypeVariants variant;
  TreeIntegralType* integralType;

  TreeNumericType(): Tree(NonTerminalType::NumericType), variant(NTNumericTypeVariants::Max), integralType(nullptr) {

  }
};

enum class NTConstructorDeclaratorVariants {
  SimpleNameLParRPar,  // SimpleName ( ) 
  SimpleNameLParFormalParameterListRPar,  // SimpleName ( FormalParameterList ) 
  Max,
};

struct TreeConstructorDeclarator: public Tree {
  enum NTConstructorDeclaratorVariants variant;
  TreeFormalParameterList* formalParameterList;
  TreeSimpleName* simpleName;

  TreeConstructorDeclarator(): Tree(NonTerminalType::ConstructorDeclarator), variant(NTConstructorDeclaratorVariants::Max), formalParameterList(nullptr) , simpleName(nullptr) {

  }
};

enum class NTUnaryExpressionNotPlusMinusVariants {
  PostfixExpression,  // PostfixExpression 
  TilUnaryExpression,  // ~ UnaryExpression 
  BangUnaryExpression,  // ! UnaryExpression 
  CastExpression,  // CastExpression 
  Max,
};

struct TreeUnaryExpressionNotPlusMinus: public Tree {
  enum NTUnaryExpressionNotPlusMinusVariants variant;
  TreePostfixExpression* postfixExpression;
  TreeCastExpression* castExpression;
  TreeUnaryExpression* unaryExpression;

  TreeUnaryExpressionNotPlusMinus(): Tree(NonTerminalType::UnaryExpressionNotPlusMinus), variant(NTUnaryExpressionNotPlusMinusVariants::Max), postfixExpression(nullptr) , castExpression(nullptr) , unaryExpression(nullptr) {

  }
};

enum class NTInterfaceBodyVariants {
  LCBrRCBr,  // { } 
  LCBrInterfaceMemberDeclarationsRCBr,  // { InterfaceMemberDeclarations } 
  Max,
};

struct TreeInterfaceBody: public Tree {
  enum NTInterfaceBodyVariants variant;
  TreeInterfaceMemberDeclarations* interfaceMemberDeclarations;

  TreeInterfaceBody(): Tree(NonTerminalType::InterfaceBody), variant(NTInterfaceBodyVariants::Max), interfaceMemberDeclarations(nullptr) {

  }
};

enum class NTPrimaryNoNewArrayVariants {
  Literal,  // Literal 
  This,  // this 
  LParExpressionRPar,  // ( Expression ) 
  ClassInstanceCreationExpression,  // ClassInstanceCreationExpression 
  FieldAccess,  // FieldAccess 
  MethodInvocation,  // MethodInvocation 
  ArrayAccess,  // ArrayAccess 
  Max,
};

struct TreePrimaryNoNewArray: public Tree {
  enum NTPrimaryNoNewArrayVariants variant;
  TreeArrayAccess* arrayAccess;
  TreeExpression* expression;
  TreeMethodInvocation* methodInvocation;
  TreeLiteral* literal;
  TreeClassInstanceCreationExpression* classInstanceCreationExpression;
  TreeFieldAccess* fieldAccess;

  TreePrimaryNoNewArray(): Tree(NonTerminalType::PrimaryNoNewArray), variant(NTPrimaryNoNewArrayVariants::Max), arrayAccess(nullptr) , expression(nullptr) , methodInvocation(nullptr) , literal(nullptr) , classInstanceCreationExpression(nullptr) , fieldAccess(nullptr) {

  }
};

enum class NTSimpleNameVariants {
  Identifier,  // Identifier 
  Max,
};

struct TreeSimpleName: public Tree {
  enum NTSimpleNameVariants variant;
  TreeIdentifier* identifier;

  TreeSimpleName(): Tree(NonTerminalType::SimpleName), variant(NTSimpleNameVariants::Max), identifier(nullptr) {

  }
};

enum class NTIntegralTypeVariants {
  byte,  // byte 
  Short,  // short 
  Int,  // int 
  Char,  // char 
  Max,
};

struct TreeIntegralType: public Tree {
  enum NTIntegralTypeVariants variant;

  TreeIntegralType(): Tree(NonTerminalType::IntegralType), variant(NTIntegralTypeVariants::Max){

  }
};

enum class NTMethodBodyVariants {
  Block,  // Block 
  SCol,  // ; 
  Max,
};

struct TreeMethodBody: public Tree {
  enum NTMethodBodyVariants variant;
  TreeBlock* block;

  TreeMethodBody(): Tree(NonTerminalType::MethodBody), variant(NTMethodBodyVariants::Max), block(nullptr) {

  }
};

enum class NTTypeImportOnDemandDeclarationVariants {
  importNameDotStarSCol,  // import Name . * ; 
  Max,
};

struct TreeTypeImportOnDemandDeclaration: public Tree {
  enum NTTypeImportOnDemandDeclarationVariants variant;
  TreeName* name;

  TreeTypeImportOnDemandDeclaration(): Tree(NonTerminalType::TypeImportOnDemandDeclaration), variant(NTTypeImportOnDemandDeclarationVariants::Max), name(nullptr) {

  }
};

enum class NTExpressionStatementVariants {
  StatementExpressionSCol,  // StatementExpression ; 
  Max,
};

struct TreeExpressionStatement: public Tree {
  enum NTExpressionStatementVariants variant;
  TreeStatementExpression* statementExpression;

  TreeExpressionStatement(): Tree(NonTerminalType::ExpressionStatement), variant(NTExpressionStatementVariants::Max), statementExpression(nullptr) {

  }
};

enum class NTIfThenElseStatementNoShortIfVariants {
  IfLParExpressionRParStatementNoShortIfElseStatementNoShortIf,  // if ( Expression ) StatementNoShortIf else StatementNoShortIf 
  Max,
};

struct TreeIfThenElseStatementNoShortIf: public Tree {
  enum NTIfThenElseStatementNoShortIfVariants variant;
  TreeStatementNoShortIf* statementNoShortIf;
  TreeExpression* expression;

  TreeIfThenElseStatementNoShortIf(): Tree(NonTerminalType::IfThenElseStatementNoShortIf), variant(NTIfThenElseStatementNoShortIfVariants::Max), statementNoShortIf(nullptr) , expression(nullptr) {

  }
};

enum class NTInterfaceDeclarationVariants {
  interfaceIdentifierInterfaceBody,  // interface Identifier InterfaceBody 
  ModifiersinterfaceIdentifierInterfaceBody,  // Modifiers interface Identifier InterfaceBody 
  interfaceIdentifierExtendsInterfacesInterfaceBody,  // interface Identifier ExtendsInterfaces InterfaceBody 
  ModifiersinterfaceIdentifierExtendsInterfacesInterfaceBody,  // Modifiers interface Identifier ExtendsInterfaces InterfaceBody 
  Max,
};

struct TreeInterfaceDeclaration: public Tree {
  enum NTInterfaceDeclarationVariants variant;
  TreeExtendsInterfaces* extendsInterfaces;
  TreeModifiers* modifiers;
  TreeIdentifier* identifier;
  TreeInterfaceBody* interfaceBody;

  TreeInterfaceDeclaration(): Tree(NonTerminalType::InterfaceDeclaration), variant(NTInterfaceDeclarationVariants::Max), extendsInterfaces(nullptr) , modifiers(nullptr) , identifier(nullptr) , interfaceBody(nullptr) {

  }
};

enum class NTExtendsInterfacesVariants {
  extendsInterfaceType,  // extends InterfaceType 
  ExtendsInterfacesComInterfaceType,  // ExtendsInterfaces , InterfaceType 
  Max,
};

struct TreeExtendsInterfaces: public Tree {
  enum NTExtendsInterfacesVariants variant;
  TreeExtendsInterfaces* extendsInterfaces;
  TreeInterfaceType* interfaceType;

  TreeExtendsInterfaces(): Tree(NonTerminalType::ExtendsInterfaces), variant(NTExtendsInterfacesVariants::Max), extendsInterfaces(nullptr) , interfaceType(nullptr) {

  }
};

enum class NTDimExprsVariants {
  DimExpr,  // DimExpr 
  DimExprsDimExpr,  // DimExprs DimExpr 
  Max,
};

struct TreeDimExprs: public Tree {
  enum NTDimExprsVariants variant;
  TreeDimExprs* dimExprs;
  TreeDimExpr* dimExpr;

  TreeDimExprs(): Tree(NonTerminalType::DimExprs), variant(NTDimExprsVariants::Max), dimExprs(nullptr) , dimExpr(nullptr) {

  }
};

enum class NTQualifiedNameVariants {
  NameDotIdentifier,  // Name . Identifier 
  Max,
};

struct TreeQualifiedName: public Tree {
  enum NTQualifiedNameVariants variant;
  TreeIdentifier* identifier;
  TreeName* name;

  TreeQualifiedName(): Tree(NonTerminalType::QualifiedName), variant(NTQualifiedNameVariants::Max), identifier(nullptr) , name(nullptr) {

  }
};

enum class NTInterfaceMemberDeclarationsVariants {
  InterfaceMemberDeclaration,  // InterfaceMemberDeclaration 
  InterfaceMemberDeclarationsInterfaceMemberDeclaration,  // InterfaceMemberDeclarations InterfaceMemberDeclaration 
  Max,
};

struct TreeInterfaceMemberDeclarations: public Tree {
  enum NTInterfaceMemberDeclarationsVariants variant;
  TreeInterfaceMemberDeclarations* interfaceMemberDeclarations;
  TreeInterfaceMemberDeclaration* interfaceMemberDeclaration;

  TreeInterfaceMemberDeclarations(): Tree(NonTerminalType::InterfaceMemberDeclarations), variant(NTInterfaceMemberDeclarationsVariants::Max), interfaceMemberDeclarations(nullptr) , interfaceMemberDeclaration(nullptr) {

  }
};

enum class NTBlockStatementVariants {
  LocalVariableDeclarationStatement,  // LocalVariableDeclarationStatement 
  Statement,  // Statement 
  Max,
};

struct TreeBlockStatement: public Tree {
  enum NTBlockStatementVariants variant;
  TreeStatement* statement;
  TreeLocalVariableDeclarationStatement* localVariableDeclarationStatement;

  TreeBlockStatement(): Tree(NonTerminalType::BlockStatement), variant(NTBlockStatementVariants::Max), statement(nullptr) , localVariableDeclarationStatement(nullptr) {

  }
};

enum class NTStringLiteralVariants {
  Max,
};

struct TreeStringLiteral: public Tree {
  enum NTStringLiteralVariants variant;

  TreeStringLiteral(): Tree(NonTerminalType::StringLiteral), variant(NTStringLiteralVariants::Max){

  }
};

enum class NTWhileStatementNoShortIfVariants {
  WhileLParExpressionRParStatementNoShortIf,  // while ( Expression ) StatementNoShortIf 
  Max,
};

struct TreeWhileStatementNoShortIf: public Tree {
  enum NTWhileStatementNoShortIfVariants variant;
  TreeStatementNoShortIf* statementNoShortIf;
  TreeExpression* expression;

  TreeWhileStatementNoShortIf(): Tree(NonTerminalType::WhileStatementNoShortIf), variant(NTWhileStatementNoShortIfVariants::Max), statementNoShortIf(nullptr) , expression(nullptr) {

  }
};

enum class NTInterfaceMemberDeclarationVariants {
  ConstantDeclaration,  // ConstantDeclaration 
  AbstractMethodDeclaration,  // AbstractMethodDeclaration 
  Max,
};

struct TreeInterfaceMemberDeclaration: public Tree {
  enum NTInterfaceMemberDeclarationVariants variant;
  TreeAbstractMethodDeclaration* abstractMethodDeclaration;
  TreeConstantDeclaration* constantDeclaration;

  TreeInterfaceMemberDeclaration(): Tree(NonTerminalType::InterfaceMemberDeclaration), variant(NTInterfaceMemberDeclarationVariants::Max), abstractMethodDeclaration(nullptr) , constantDeclaration(nullptr) {

  }
};

enum class NTPostfixExpressionVariants {
  Primary,  // Primary 
  Name,  // Name 
  Max,
};

struct TreePostfixExpression: public Tree {
  enum NTPostfixExpressionVariants variant;
  TreeName* name;
  TreePrimary* primary;

  TreePostfixExpression(): Tree(NonTerminalType::PostfixExpression), variant(NTPostfixExpressionVariants::Max), name(nullptr) , primary(nullptr) {

  }
};

enum class NTConstantDeclarationVariants {
  FieldDeclaration,  // FieldDeclaration 
  Max,
};

struct TreeConstantDeclaration: public Tree {
  enum NTConstantDeclarationVariants variant;
  TreeFieldDeclaration* fieldDeclaration;

  TreeConstantDeclaration(): Tree(NonTerminalType::ConstantDeclaration), variant(NTConstantDeclarationVariants::Max), fieldDeclaration(nullptr) {

  }
};

enum class NTAbstractMethodDeclarationVariants {
  MethodHeaderSCol,  // MethodHeader ; 
  Max,
};

struct TreeAbstractMethodDeclaration: public Tree {
  enum NTAbstractMethodDeclarationVariants variant;
  TreeMethodHeader* methodHeader;

  TreeAbstractMethodDeclaration(): Tree(NonTerminalType::AbstractMethodDeclaration), variant(NTAbstractMethodDeclarationVariants::Max), methodHeader(nullptr) {

  }
};

enum class NTSuperVariants {
  extendsClassType,  // extends ClassType 
  Max,
};

struct TreeSuper: public Tree {
  enum NTSuperVariants variant;
  TreeClassType* classType;

  TreeSuper(): Tree(NonTerminalType::Super), variant(NTSuperVariants::Max), classType(nullptr) {

  }
};

enum class NTArrayInitializerVariants {
  LCBrRCBr,  // { } 
  LCBrVariableInitializersRCBr,  // { VariableInitializers } 
  LCBrComRCBr,  // { , } 
  LCBrVariableInitializersComRCBr,  // { VariableInitializers , } 
  Max,
};

struct TreeArrayInitializer: public Tree {
  enum NTArrayInitializerVariants variant;
  TreeVariableInitializers* variableInitializers;

  TreeArrayInitializer(): Tree(NonTerminalType::ArrayInitializer), variant(NTArrayInitializerVariants::Max), variableInitializers(nullptr) {

  }
};

enum class NTReturnStatementVariants {
  ReturnSCol,  // return ; 
  ReturnExpressionSCol,  // return Expression ; 
  Max,
};

struct TreeReturnStatement: public Tree {
  enum NTReturnStatementVariants variant;
  TreeExpression* expression;

  TreeReturnStatement(): Tree(NonTerminalType::ReturnStatement), variant(NTReturnStatementVariants::Max), expression(nullptr) {

  }
};

enum class NTVariableInitializersVariants {
  VariableInitializer,  // VariableInitializer 
  VariableInitializersComVariableInitializer,  // VariableInitializers , VariableInitializer 
  Max,
};

struct TreeVariableInitializers: public Tree {
  enum NTVariableInitializersVariants variant;
  TreeVariableInitializers* variableInitializers;
  TreeVariableInitializer* variableInitializer;

  TreeVariableInitializers(): Tree(NonTerminalType::VariableInitializers), variant(NTVariableInitializersVariants::Max), variableInitializers(nullptr) , variableInitializer(nullptr) {

  }
};

enum class NTImportDeclarationVariants {
  SingleTypeImportDeclaration,  // SingleTypeImportDeclaration 
  TypeImportOnDemandDeclaration,  // TypeImportOnDemandDeclaration 
  Max,
};

struct TreeImportDeclaration: public Tree {
  enum NTImportDeclarationVariants variant;
  TreeTypeImportOnDemandDeclaration* typeImportOnDemandDeclaration;
  TreeSingleTypeImportDeclaration* singleTypeImportDeclaration;

  TreeImportDeclaration(): Tree(NonTerminalType::ImportDeclaration), variant(NTImportDeclarationVariants::Max), typeImportOnDemandDeclaration(nullptr) , singleTypeImportDeclaration(nullptr) {

  }
};

enum class NTForStatementNoShortIfVariants {
  ForLParSColSColRParStatementNoShortIf,  // for ( ; ; ) StatementNoShortIf 
  ForLParForInitSColSColRParStatementNoShortIf,  // for ( ForInit ; ; ) StatementNoShortIf 
  ForLParSColExpressionSColRParStatementNoShortIf,  // for ( ; Expression ; ) StatementNoShortIf 
  ForLParForInitSColExpressionSColRParStatementNoShortIf,  // for ( ForInit ; Expression ; ) StatementNoShortIf 
  ForLParSColSColForUpdateRParStatementNoShortIf,  // for ( ; ; ForUpdate ) StatementNoShortIf 
  ForLParForInitSColSColForUpdateRParStatementNoShortIf,  // for ( ForInit ; ; ForUpdate ) StatementNoShortIf 
  ForLParSColExpressionSColForUpdateRParStatementNoShortIf,  // for ( ; Expression ; ForUpdate ) StatementNoShortIf 
  ForLParForInitSColExpressionSColForUpdateRParStatementNoShortIf,  // for ( ForInit ; Expression ; ForUpdate ) StatementNoShortIf 
  Max,
};

struct TreeForStatementNoShortIf: public Tree {
  enum NTForStatementNoShortIfVariants variant;
  TreeForUpdate* forUpdate;
  TreeExpression* expression;
  TreeStatementNoShortIf* statementNoShortIf;
  TreeForInit* forInit;

  TreeForStatementNoShortIf(): Tree(NonTerminalType::ForStatementNoShortIf), variant(NTForStatementNoShortIfVariants::Max), forUpdate(nullptr) , expression(nullptr) , statementNoShortIf(nullptr) , forInit(nullptr) {

  }
};

enum class NTBlockVariants {
  LCBrRCBr,  // { } 
  LCBrBlockStatementsRCBr,  // { BlockStatements } 
  Max,
};

struct TreeBlock: public Tree {
  enum NTBlockVariants variant;
  TreeBlockStatements* blockStatements;

  TreeBlock(): Tree(NonTerminalType::Block), variant(NTBlockVariants::Max), blockStatements(nullptr) {

  }
};

enum class NTTypeDeclarationsVariants {
  TypeDeclaration,  // TypeDeclaration 
  TypeDeclarationsTypeDeclaration,  // TypeDeclarations TypeDeclaration 
  Max,
};

struct TreeTypeDeclarations: public Tree {
  enum NTTypeDeclarationsVariants variant;
  TreeTypeDeclarations* typeDeclarations;
  TreeTypeDeclaration* typeDeclaration;

  TreeTypeDeclarations(): Tree(NonTerminalType::TypeDeclarations), variant(NTTypeDeclarationsVariants::Max), typeDeclarations(nullptr) , typeDeclaration(nullptr) {

  }
};

enum class NTLocalVariableDeclarationStatementVariants {
  LocalVariableDeclarationSCol,  // LocalVariableDeclaration ; 
  Max,
};

struct TreeLocalVariableDeclarationStatement: public Tree {
  enum NTLocalVariableDeclarationStatementVariants variant;
  TreeLocalVariableDeclaration* localVariableDeclaration;

  TreeLocalVariableDeclarationStatement(): Tree(NonTerminalType::LocalVariableDeclarationStatement), variant(NTLocalVariableDeclarationStatementVariants::Max), localVariableDeclaration(nullptr) {

  }
};

enum class NTStaticInitializerVariants {
  StaticBlock,  // static Block 
  Max,
};

struct TreeStaticInitializer: public Tree {
  enum NTStaticInitializerVariants variant;
  TreeBlock* block;

  TreeStaticInitializer(): Tree(NonTerminalType::StaticInitializer), variant(NTStaticInitializerVariants::Max), block(nullptr) {

  }
};

enum class NTIntegerLiteralVariants {
  Max,
};

struct TreeIntegerLiteral: public Tree {
  enum NTIntegerLiteralVariants variant;

  TreeIntegerLiteral(): Tree(NonTerminalType::IntegerLiteral), variant(NTIntegerLiteralVariants::Max){

  }
};

enum class NTStatementVariants {
  StatementWithoutTrailingSubstatement,  // StatementWithoutTrailingSubstatement 
  IfThenStatement,  // IfThenStatement 
  IfThenElseStatement,  // IfThenElseStatement 
  WhileStatement,  // WhileStatement 
  ForStatement,  // ForStatement 
  Max,
};

struct TreeStatement: public Tree {
  enum NTStatementVariants variant;
  TreeForStatement* forStatement;
  TreeIfThenElseStatement* ifThenElseStatement;
  TreeWhileStatement* whileStatement;
  TreeStatementWithoutTrailingSubstatement* statementWithoutTrailingSubstatement;
  TreeIfThenStatement* ifThenStatement;

  TreeStatement(): Tree(NonTerminalType::Statement), variant(NTStatementVariants::Max), forStatement(nullptr) , ifThenElseStatement(nullptr) , whileStatement(nullptr) , statementWithoutTrailingSubstatement(nullptr) , ifThenStatement(nullptr) {

  }
};

enum class NTArrayAccessVariants {
  NameLSBrExpressionRSBr,  // Name [ Expression ] 
  PrimaryNoNewArrayLSBrExpressionRSBr,  // PrimaryNoNewArray [ Expression ] 
  Max,
};

struct TreeArrayAccess: public Tree {
  enum NTArrayAccessVariants variant;
  TreePrimaryNoNewArray* primaryNoNewArray;
  TreeName* name;
  TreeExpression* expression;

  TreeArrayAccess(): Tree(NonTerminalType::ArrayAccess), variant(NTArrayAccessVariants::Max), primaryNoNewArray(nullptr) , name(nullptr) , expression(nullptr) {

  }
};

enum class NTStatementNoShortIfVariants {
  StatementWithoutTrailingSubstatement,  // StatementWithoutTrailingSubstatement 
  IfThenElseStatementNoShortIf,  // IfThenElseStatementNoShortIf 
  WhileStatementNoShortIf,  // WhileStatementNoShortIf 
  ForStatementNoShortIf,  // ForStatementNoShortIf 
  Max,
};

struct TreeStatementNoShortIf: public Tree {
  enum NTStatementNoShortIfVariants variant;
  TreeForStatementNoShortIf* forStatementNoShortIf;
  TreeWhileStatementNoShortIf* whileStatementNoShortIf;
  TreeStatementWithoutTrailingSubstatement* statementWithoutTrailingSubstatement;
  TreeIfThenElseStatementNoShortIf* ifThenElseStatementNoShortIf;

  TreeStatementNoShortIf(): Tree(NonTerminalType::StatementNoShortIf), variant(NTStatementNoShortIfVariants::Max), forStatementNoShortIf(nullptr) , whileStatementNoShortIf(nullptr) , statementWithoutTrailingSubstatement(nullptr) , ifThenElseStatementNoShortIf(nullptr) {

  }
};

enum class NTEmptyStatementVariants {
  SCol,  // ; 
  Max,
};

struct TreeEmptyStatement: public Tree {
  enum NTEmptyStatementVariants variant;

  TreeEmptyStatement(): Tree(NonTerminalType::EmptyStatement), variant(NTEmptyStatementVariants::Max){

  }
};

enum class NTForStatementVariants {
  ForLParSColSColRParStatement,  // for ( ; ; ) Statement 
  ForLParForInitSColSColRParStatement,  // for ( ForInit ; ; ) Statement 
  ForLParSColExpressionSColRParStatement,  // for ( ; Expression ; ) Statement 
  ForLParForInitSColExpressionSColRParStatement,  // for ( ForInit ; Expression ; ) Statement 
  ForLParSColSColForUpdateRParStatement,  // for ( ; ; ForUpdate ) Statement 
  ForLParForInitSColSColForUpdateRParStatement,  // for ( ForInit ; ; ForUpdate ) Statement 
  ForLParSColExpressionSColForUpdateRParStatement,  // for ( ; Expression ; ForUpdate ) Statement 
  ForLParForInitSColExpressionSColForUpdateRParStatement,  // for ( ForInit ; Expression ; ForUpdate ) Statement 
  Max,
};

struct TreeForStatement: public Tree {
  enum NTForStatementVariants variant;
  TreeForUpdate* forUpdate;
  TreeExpression* expression;
  TreeStatement* statement;
  TreeForInit* forInit;

  TreeForStatement(): Tree(NonTerminalType::ForStatement), variant(NTForStatementVariants::Max), forUpdate(nullptr) , expression(nullptr) , statement(nullptr) , forInit(nullptr) {

  }
};

enum class NTIfThenStatementVariants {
  IfLParExpressionRParStatement,  // if ( Expression ) Statement 
  Max,
};

struct TreeIfThenStatement: public Tree {
  enum NTIfThenStatementVariants variant;
  TreeStatement* statement;
  TreeExpression* expression;

  TreeIfThenStatement(): Tree(NonTerminalType::IfThenStatement), variant(NTIfThenStatementVariants::Max), statement(nullptr) , expression(nullptr) {

  }
};

enum class NTVariableDeclaratorIdVariants {
  Identifier,  // Identifier 
  VariableDeclaratorIdLSBrRSBr,  // VariableDeclaratorId [ ] 
  Max,
};

struct TreeVariableDeclaratorId: public Tree {
  enum NTVariableDeclaratorIdVariants variant;
  TreeVariableDeclaratorId* variableDeclaratorId;
  TreeIdentifier* identifier;

  TreeVariableDeclaratorId(): Tree(NonTerminalType::VariableDeclaratorId), variant(NTVariableDeclaratorIdVariants::Max), variableDeclaratorId(nullptr) , identifier(nullptr) {

  }
};

enum class NTNullLiteralVariants {
  Max,
};

struct TreeNullLiteral: public Tree {
  enum NTNullLiteralVariants variant;

  TreeNullLiteral(): Tree(NonTerminalType::NullLiteral), variant(NTNullLiteralVariants::Max){

  }
};

enum class NTArgumentListVariants {
  Expression,  // Expression 
  ArgumentListComExpression,  // ArgumentList , Expression 
  Max,
};

struct TreeArgumentList: public Tree {
  enum NTArgumentListVariants variant;
  TreeArgumentList* argumentList;
  TreeExpression* expression;

  TreeArgumentList(): Tree(NonTerminalType::ArgumentList), variant(NTArgumentListVariants::Max), argumentList(nullptr) , expression(nullptr) {

  }
};

enum class NTIfThenElseStatementVariants {
  IfLParExpressionRParStatementNoShortIfElseStatement,  // if ( Expression ) StatementNoShortIf else Statement 
  Max,
};

struct TreeIfThenElseStatement: public Tree {
  enum NTIfThenElseStatementVariants variant;
  TreeStatement* statement;
  TreeExpression* expression;
  TreeStatementNoShortIf* statementNoShortIf;

  TreeIfThenElseStatement(): Tree(NonTerminalType::IfThenElseStatement), variant(NTIfThenElseStatementVariants::Max), statement(nullptr) , expression(nullptr) , statementNoShortIf(nullptr) {

  }
};

enum class NTWhileStatementVariants {
  WhileLParExpressionRParStatement,  // while ( Expression ) Statement 
  Max,
};

struct TreeWhileStatement: public Tree {
  enum NTWhileStatementVariants variant;
  TreeStatement* statement;
  TreeExpression* expression;

  TreeWhileStatement(): Tree(NonTerminalType::WhileStatement), variant(NTWhileStatementVariants::Max), statement(nullptr) , expression(nullptr) {

  }
};

enum class NTPrimaryVariants {
  PrimaryNoNewArray,  // PrimaryNoNewArray 
  ArrayCreationExpression,  // ArrayCreationExpression 
  Max,
};

struct TreePrimary: public Tree {
  enum NTPrimaryVariants variant;
  TreeArrayCreationExpression* arrayCreationExpression;
  TreePrimaryNoNewArray* primaryNoNewArray;

  TreePrimary(): Tree(NonTerminalType::Primary), variant(NTPrimaryVariants::Max), arrayCreationExpression(nullptr) , primaryNoNewArray(nullptr) {

  }
};

enum class NTForInitVariants {
  StatementExpression,  // StatementExpression 
  LocalVariableDeclaration,  // LocalVariableDeclaration 
  Max,
};

struct TreeForInit: public Tree {
  enum NTForInitVariants variant;
  TreeLocalVariableDeclaration* localVariableDeclaration;
  TreeStatementExpression* statementExpression;

  TreeForInit(): Tree(NonTerminalType::ForInit), variant(NTForInitVariants::Max), localVariableDeclaration(nullptr) , statementExpression(nullptr) {

  }
};

enum class NTConditionalAndExpressionVariants {
  EqualityExpression,  // EqualityExpression 
  ConditionalAndExpressionAmpAmpEqualityExpression,  // ConditionalAndExpression && EqualityExpression 
  Max,
};

struct TreeConditionalAndExpression: public Tree {
  enum NTConditionalAndExpressionVariants variant;
  TreeConditionalAndExpression* conditionalAndExpression;
  TreeEqualityExpression* equalityExpression;

  TreeConditionalAndExpression(): Tree(NonTerminalType::ConditionalAndExpression), variant(NTConditionalAndExpressionVariants::Max), conditionalAndExpression(nullptr) , equalityExpression(nullptr) {

  }
};

enum class NTForUpdateVariants {
  StatementExpression,  // StatementExpression 
  Max,
};

struct TreeForUpdate: public Tree {
  enum NTForUpdateVariants variant;
  TreeStatementExpression* statementExpression;

  TreeForUpdate(): Tree(NonTerminalType::ForUpdate), variant(NTForUpdateVariants::Max), statementExpression(nullptr) {

  }
};

enum class NTUnaryExpressionVariants {
  MinusUnaryExpression,  // - UnaryExpression 
  UnaryExpressionNotPlusMinus,  // UnaryExpressionNotPlusMinus 
  Max,
};

struct TreeUnaryExpression: public Tree {
  enum NTUnaryExpressionVariants variant;
  TreeUnaryExpressionNotPlusMinus* unaryExpressionNotPlusMinus;
  TreeUnaryExpression* unaryExpression;

  TreeUnaryExpression(): Tree(NonTerminalType::UnaryExpression), variant(NTUnaryExpressionVariants::Max), unaryExpressionNotPlusMinus(nullptr) , unaryExpression(nullptr) {

  }
};

enum class NTDimsVariants {
  LSBrRSBr,  // [ ] 
  DimsLSBrRSBr,  // Dims [ ] 
  Max,
};

struct TreeDims: public Tree {
  enum NTDimsVariants variant;
  TreeDims* dims;

  TreeDims(): Tree(NonTerminalType::Dims), variant(NTDimsVariants::Max), dims(nullptr) {

  }
};

enum class NTBlockStatementsVariants {
  BlockStatement,  // BlockStatement 
  BlockStatementsBlockStatement,  // BlockStatements BlockStatement 
  Max,
};

struct TreeBlockStatements: public Tree {
  enum NTBlockStatementsVariants variant;
  TreeBlockStatements* blockStatements;
  TreeBlockStatement* blockStatement;

  TreeBlockStatements(): Tree(NonTerminalType::BlockStatements), variant(NTBlockStatementsVariants::Max), blockStatements(nullptr) , blockStatement(nullptr) {

  }
};

enum class NTFieldAccessVariants {
  PrimaryDotIdentifier,  // Primary . Identifier 
  Max,
};

struct TreeFieldAccess: public Tree {
  enum NTFieldAccessVariants variant;
  TreeIdentifier* identifier;
  TreePrimary* primary;

  TreeFieldAccess(): Tree(NonTerminalType::FieldAccess), variant(NTFieldAccessVariants::Max), identifier(nullptr) , primary(nullptr) {

  }
};

enum class NTMethodInvocationVariants {
  NameLParRPar,  // Name ( ) 
  NameLParArgumentListRPar,  // Name ( ArgumentList ) 
  PrimaryDotIdentifierLParRPar,  // Primary . Identifier ( ) 
  PrimaryDotIdentifierLParArgumentListRPar,  // Primary . Identifier ( ArgumentList ) 
  Max,
};

struct TreeMethodInvocation: public Tree {
  enum NTMethodInvocationVariants variant;
  TreeIdentifier* identifier;
  TreePrimary* primary;
  TreeName* name;
  TreeArgumentList* argumentList;

  TreeMethodInvocation(): Tree(NonTerminalType::MethodInvocation), variant(NTMethodInvocationVariants::Max), identifier(nullptr) , primary(nullptr) , name(nullptr) , argumentList(nullptr) {

  }
};

} // namespace Parse 
