#pragma once
#include "parserASTBase.h"
namespace Parse { 
enum class NTExpressionVariants {
  AssignmentExpression,  // AssignmentExpression 
  Max,
};

struct TreeExpression: public Tree {
  enum NTExpressionVariants variant;
  TreeAssignmentExpression* AssignmentExpression;
};

enum class NTAssignmentVariants {
  LeftHandSideEqAssignmentExpression,  // LeftHandSide = AssignmentExpression 
  Max,
};

struct TreeAssignment: public Tree {
  enum NTAssignmentVariants variant;
  TreeAssignmentExpression* AssignmentExpression;
  TreeLeftHandSide* LeftHandSide;
};

enum class NTConditionalOrExpressionVariants {
  ConditionalAndExpression,  // ConditionalAndExpression 
  ConditionalOrExpressionOrOrConditionalAndExpression,  // ConditionalOrExpression || ConditionalAndExpression 
  Max,
};

struct TreeConditionalOrExpression: public Tree {
  enum NTConditionalOrExpressionVariants variant;
  TreeConditionalOrExpression* ConditionalOrExpression;
  TreeConditionalAndExpression* ConditionalAndExpression;
};

enum class NTSingleTypeImportDeclarationVariants {
  importNameSCol,  // import Name ; 
  Max,
};

struct TreeSingleTypeImportDeclaration: public Tree {
  enum NTSingleTypeImportDeclarationVariants variant;
  TreeName* Name;
};

enum class NTConstructorDeclaratorVariants {
  SimpleNameLParRPar,  // SimpleName ( ) 
  SimpleNameLParFormalParameterListRPar,  // SimpleName ( FormalParameterList ) 
  Max,
};

struct TreeConstructorDeclarator: public Tree {
  enum NTConstructorDeclaratorVariants variant;
  TreeFormalParameterList* FormalParameterList;
  TreeSimpleName* SimpleName;
};

enum class NTNumericTypeVariants {
  IntegralType,  // IntegralType 
  Max,
};

struct TreeNumericType: public Tree {
  enum NTNumericTypeVariants variant;
  TreeIntegralType* IntegralType;
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
  TreeArrayAccess* ArrayAccess;
  TreeExpression* Expression;
  TreeMethodInvocation* MethodInvocation;
  TreeLiteral* Literal;
  TreeClassInstanceCreationExpression* ClassInstanceCreationExpression;
  TreeFieldAccess* FieldAccess;
};

enum class NTMethodDeclaratorVariants {
  IdentifierLParRPar,  // Identifier ( ) 
  IdentifierLParFormalParameterListRPar,  // Identifier ( FormalParameterList ) 
  MethodDeclaratorLSBrRSBr,  // MethodDeclarator [ ] 
  Max,
};

struct TreeMethodDeclarator: public Tree {
  enum NTMethodDeclaratorVariants variant;
  TreeMethodDeclarator* MethodDeclarator;
  TreeIdentifier* Identifier;
  TreeFormalParameterList* FormalParameterList;
};

enum class NTVariableInitializerVariants {
  Expression,  // Expression 
  ArrayInitializer,  // ArrayInitializer 
  Max,
};

struct TreeVariableInitializer: public Tree {
  enum NTVariableInitializerVariants variant;
  TreeArrayInitializer* ArrayInitializer;
  TreeExpression* Expression;
};

enum class NTFieldDeclarationVariants {
  TypeVariableDeclaratorSCol,  // Type VariableDeclarator ; 
  ModifiersTypeVariableDeclaratorSCol,  // Modifiers Type VariableDeclarator ; 
  Max,
};

struct TreeFieldDeclaration: public Tree {
  enum NTFieldDeclarationVariants variant;
  TreeType* Type;
  TreeModifiers* Modifiers;
  TreeVariableDeclarator* VariableDeclarator;
};

enum class NTInterfacesVariants {
  implementsInterfaceTypeList,  // implements InterfaceTypeList 
  Max,
};

struct TreeInterfaces: public Tree {
  enum NTInterfacesVariants variant;
  TreeInterfaceTypeList* InterfaceTypeList;
};

enum class NTClassBodyDeclarationsVariants {
  ClassBodyDeclaration,  // ClassBodyDeclaration 
  ClassBodyDeclarationsClassBodyDeclaration,  // ClassBodyDeclarations ClassBodyDeclaration 
  Max,
};

struct TreeClassBodyDeclarations: public Tree {
  enum NTClassBodyDeclarationsVariants variant;
  TreeClassBodyDeclarations* ClassBodyDeclarations;
  TreeClassBodyDeclaration* ClassBodyDeclaration;
};

enum class NTInterfaceTypeListVariants {
  InterfaceType,  // InterfaceType 
  InterfaceTypeListComInterfaceType,  // InterfaceTypeList , InterfaceType 
  Max,
};

struct TreeInterfaceTypeList: public Tree {
  enum NTInterfaceTypeListVariants variant;
  TreeInterfaceTypeList* InterfaceTypeList;
  TreeInterfaceType* InterfaceType;
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
  TreeInterfaces* Interfaces;
  TreeSuper* Super;
  TreeModifiers* Modifiers;
  TreeIdentifier* Identifier;
  TreeClassBody* ClassBody;
};

enum class NTConstantExpressionVariants {
  Expression,  // Expression 
  Max,
};

struct TreeConstantExpression: public Tree {
  enum NTConstantExpressionVariants variant;
  TreeExpression* Expression;
};

enum class NTClassInstanceCreationExpressionVariants {
  NewClassTypeLParRPar,  // new ClassType ( ) 
  NewClassTypeLParArgumentListRPar,  // new ClassType ( ArgumentList ) 
  Max,
};

struct TreeClassInstanceCreationExpression: public Tree {
  enum NTClassInstanceCreationExpressionVariants variant;
  TreeArgumentList* ArgumentList;
  TreeClassType* ClassType;
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
};

enum class NTConstructorDeclarationVariants {
  ConstructorDeclaratorConstructorBody,  // ConstructorDeclarator ConstructorBody 
  ModifiersConstructorDeclaratorConstructorBody,  // Modifiers ConstructorDeclarator ConstructorBody 
  Max,
};

struct TreeConstructorDeclaration: public Tree {
  enum NTConstructorDeclarationVariants variant;
  TreeModifiers* Modifiers;
  TreeConstructorDeclarator* ConstructorDeclarator;
  TreeConstructorBody* ConstructorBody;
};

enum class NTClassTypeListVariants {
  ClassType,  // ClassType 
  ClassTypeListComClassType,  // ClassTypeList , ClassType 
  Max,
};

struct TreeClassTypeList: public Tree {
  enum NTClassTypeListVariants variant;
  TreeClassTypeList* ClassTypeList;
  TreeClassType* ClassType;
};

enum class NTTypeVariants {
  PrimitiveType,  // PrimitiveType 
  ReferenceType,  // ReferenceType 
  Max,
};

struct TreeType: public Tree {
  enum NTTypeVariants variant;
  TreeReferenceType* ReferenceType;
  TreePrimitiveType* PrimitiveType;
};

enum class NTInterfaceBodyVariants {
  LCBrRCBr,  // { } 
  LCBrInterfaceMemberDeclarationsRCBr,  // { InterfaceMemberDeclarations } 
  Max,
};

struct TreeInterfaceBody: public Tree {
  enum NTInterfaceBodyVariants variant;
  TreeInterfaceMemberDeclarations* InterfaceMemberDeclarations;
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
  TreePostfixExpression* PostfixExpression;
  TreeCastExpression* CastExpression;
  TreeUnaryExpression* UnaryExpression;
};

enum class NTArrayTypeVariants {
  PrimitiveTypeLSBrRSBr,  // PrimitiveType [ ] 
  NameLSBrRSBr,  // Name [ ] 
  ArrayTypeLSBrRSBr,  // ArrayType [ ] 
  Max,
};

struct TreeArrayType: public Tree {
  enum NTArrayTypeVariants variant;
  TreeArrayType* ArrayType;
  TreePrimitiveType* PrimitiveType;
  TreeName* Name;
};

enum class NTClassTypeVariants {
  ClassOrInterfaceType,  // ClassOrInterfaceType 
  Max,
};

struct TreeClassType: public Tree {
  enum NTClassTypeVariants variant;
  TreeClassOrInterfaceType* ClassOrInterfaceType;
};

enum class NTAssignmentExpressionVariants {
  ConditionalOrExpression,  // ConditionalOrExpression 
  Assignment,  // Assignment 
  Max,
};

struct TreeAssignmentExpression: public Tree {
  enum NTAssignmentExpressionVariants variant;
  TreeAssignment* Assignment;
  TreeConditionalOrExpression* ConditionalOrExpression;
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
  TreeReferenceType* ReferenceType;
  TreeAdditiveExpression* AdditiveExpression;
  TreeRelationalExpression* RelationalExpression;
};

enum class NTClassBodyVariants {
  LCBrRCBr,  // { } 
  LCBrClassBodyDeclarationsRCBr,  // { ClassBodyDeclarations } 
  Max,
};

struct TreeClassBody: public Tree {
  enum NTClassBodyVariants variant;
  TreeClassBodyDeclarations* ClassBodyDeclarations;
};

enum class NTNameVariants {
  SimpleName,  // SimpleName 
  QualifiedName,  // QualifiedName 
  Max,
};

struct TreeName: public Tree {
  enum NTNameVariants variant;
  TreeQualifiedName* QualifiedName;
  TreeSimpleName* SimpleName;
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
  TreeClassOrInterfaceType* ClassOrInterfaceType;
  TreeDims* Dims;
  TreePrimitiveType* PrimitiveType;
  TreeDimExprs* DimExprs;
};

enum class NTClassOrInterfaceTypeVariants {
  Name,  // Name 
  Max,
};

struct TreeClassOrInterfaceType: public Tree {
  enum NTClassOrInterfaceTypeVariants variant;
  TreeName* Name;
};

enum class NTTypeImportOnDemandDeclarationVariants {
  importNameDotStarSCol,  // import Name . * ; 
  Max,
};

struct TreeTypeImportOnDemandDeclaration: public Tree {
  enum NTTypeImportOnDemandDeclarationVariants variant;
  TreeName* Name;
};

enum class NTIfThenElseStatementNoShortIfVariants {
  IfLParExpressionRParStatementNoShortIfElseStatementNoShortIf,  // if ( Expression ) StatementNoShortIf else StatementNoShortIf 
  Max,
};

struct TreeIfThenElseStatementNoShortIf: public Tree {
  enum NTIfThenElseStatementNoShortIfVariants variant;
  TreeStatementNoShortIf* StatementNoShortIf;
  TreeExpression* Expression;
};

enum class NTExpressionStatementVariants {
  StatementExpressionSCol,  // StatementExpression ; 
  Max,
};

struct TreeExpressionStatement: public Tree {
  enum NTExpressionStatementVariants variant;
  TreeStatementExpression* StatementExpression;
};

enum class NTInterfaceTypeVariants {
  ClassOrInterfaceType,  // ClassOrInterfaceType 
  Max,
};

struct TreeInterfaceType: public Tree {
  enum NTInterfaceTypeVariants variant;
  TreeClassOrInterfaceType* ClassOrInterfaceType;
};

enum class NTLeftHandSideVariants {
  Name,  // Name 
  FieldAccess,  // FieldAccess 
  ArrayAccess,  // ArrayAccess 
  Max,
};

struct TreeLeftHandSide: public Tree {
  enum NTLeftHandSideVariants variant;
  TreeName* Name;
  TreeArrayAccess* ArrayAccess;
  TreeFieldAccess* FieldAccess;
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
  TreeTypeDeclarations* TypeDeclarations;
  TreePackageDeclaration* PackageDeclaration;
  TreeImportDeclarations* ImportDeclarations;
};

enum class NTReferenceTypeVariants {
  ClassOrInterfaceType,  // ClassOrInterfaceType 
  ArrayType,  // ArrayType 
  Max,
};

struct TreeReferenceType: public Tree {
  enum NTReferenceTypeVariants variant;
  TreeArrayType* ArrayType;
  TreeClassOrInterfaceType* ClassOrInterfaceType;
};

enum class NTImportDeclarationsVariants {
  ImportDeclaration,  // ImportDeclaration 
  ImportDeclarationsImportDeclaration,  // ImportDeclarations ImportDeclaration 
  Max,
};

struct TreeImportDeclarations: public Tree {
  enum NTImportDeclarationsVariants variant;
  TreeImportDeclarations* ImportDeclarations;
  TreeImportDeclaration* ImportDeclaration;
};

enum class NTFormalParameterVariants {
  TypeVariableDeclaratorId,  // Type VariableDeclaratorId 
  Max,
};

struct TreeFormalParameter: public Tree {
  enum NTFormalParameterVariants variant;
  TreeVariableDeclaratorId* VariableDeclaratorId;
  TreeType* Type;
};

enum class NTStatementExpressionVariants {
  Assignment,  // Assignment 
  MethodInvocation,  // MethodInvocation 
  ClassInstanceCreationExpression,  // ClassInstanceCreationExpression 
  Max,
};

struct TreeStatementExpression: public Tree {
  enum NTStatementExpressionVariants variant;
  TreeClassInstanceCreationExpression* ClassInstanceCreationExpression;
  TreeAssignment* Assignment;
  TreeMethodInvocation* MethodInvocation;
};

enum class NTFormalParameterListVariants {
  FormalParameter,  // FormalParameter 
  FormalParameterListComFormalParameter,  // FormalParameterList , FormalParameter 
  Max,
};

struct TreeFormalParameterList: public Tree {
  enum NTFormalParameterListVariants variant;
  TreeFormalParameterList* FormalParameterList;
  TreeFormalParameter* FormalParameter;
};

enum class NTMethodDeclarationVariants {
  MethodHeaderMethodBody,  // MethodHeader MethodBody 
  Max,
};

struct TreeMethodDeclaration: public Tree {
  enum NTMethodDeclarationVariants variant;
  TreeMethodBody* MethodBody;
  TreeMethodHeader* MethodHeader;
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
  TreeNullLiteral* NullLiteral;
  TreeCharacterLiteral* CharacterLiteral;
  TreeIntegerLiteral* IntegerLiteral;
  TreeStringLiteral* StringLiteral;
  TreeBooleanLiteral* BooleanLiteral;
};

enum class NTPackageDeclarationVariants {
  packageNameSCol,  // package Name ; 
  Max,
};

struct TreePackageDeclaration: public Tree {
  enum NTPackageDeclarationVariants variant;
  TreeName* Name;
};

enum class NTVariableDeclaratorVariants {
  VariableDeclaratorId,  // VariableDeclaratorId 
  VariableDeclaratorIdEqVariableInitializer,  // VariableDeclaratorId = VariableInitializer 
  Max,
};

struct TreeVariableDeclarator: public Tree {
  enum NTVariableDeclaratorVariants variant;
  TreeVariableInitializer* VariableInitializer;
  TreeVariableDeclaratorId* VariableDeclaratorId;
};

enum class NTDimExprVariants {
  LSBrExpressionRSBr,  // [ Expression ] 
  Max,
};

struct TreeDimExpr: public Tree {
  enum NTDimExprVariants variant;
  TreeExpression* Expression;
};

enum class NTGoalVariants {
  BOFCompilationUnitEof,  // BOF CompilationUnit EOF 
  Max,
};

struct TreeGoal: public Tree {
  enum NTGoalVariants variant;
  TreeCompilationUnit* CompilationUnit;
};

enum class NTSimpleNameVariants {
  Identifier,  // Identifier 
  Max,
};

struct TreeSimpleName: public Tree {
  enum NTSimpleNameVariants variant;
  TreeIdentifier* Identifier;
};

enum class NTClassBodyDeclarationVariants {
  ClassMemberDeclaration,  // ClassMemberDeclaration 
  StaticInitializer,  // StaticInitializer 
  ConstructorDeclaration,  // ConstructorDeclaration 
  Max,
};

struct TreeClassBodyDeclaration: public Tree {
  enum NTClassBodyDeclarationVariants variant;
  TreeConstructorDeclaration* ConstructorDeclaration;
  TreeClassMemberDeclaration* ClassMemberDeclaration;
  TreeStaticInitializer* StaticInitializer;
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
  TreeModifiers* Modifiers;
  TreeType* Type;
  TreeMethodDeclarator* MethodDeclarator;
};

enum class NTModifiersVariants {
  Modifier,  // Modifier 
  ModifiersModifier,  // Modifiers Modifier 
  Max,
};

struct TreeModifiers: public Tree {
  enum NTModifiersVariants variant;
  TreeModifiers* Modifiers;
  TreeModifier* Modifier;
};

enum class NTMethodBodyVariants {
  Block,  // Block 
  SCol,  // ; 
  Max,
};

struct TreeMethodBody: public Tree {
  enum NTMethodBodyVariants variant;
  TreeBlock* Block;
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
};

enum class NTTypeDeclarationVariants {
  ClassDeclaration,  // ClassDeclaration 
  InterfaceDeclaration,  // InterfaceDeclaration 
  SCol,  // ; 
  Max,
};

struct TreeTypeDeclaration: public Tree {
  enum NTTypeDeclarationVariants variant;
  TreeInterfaceDeclaration* InterfaceDeclaration;
  TreeClassDeclaration* ClassDeclaration;
};

enum class NTPrimitiveTypeVariants {
  NumericType,  // NumericType 
  boolean,  // boolean 
  Max,
};

struct TreePrimitiveType: public Tree {
  enum NTPrimitiveTypeVariants variant;
  TreeNumericType* NumericType;
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
  TreeExtendsInterfaces* ExtendsInterfaces;
  TreeModifiers* Modifiers;
  TreeIdentifier* Identifier;
  TreeInterfaceBody* InterfaceBody;
};

enum class NTExtendsInterfacesVariants {
  extendsInterfaceType,  // extends InterfaceType 
  ExtendsInterfacesComInterfaceType,  // ExtendsInterfaces , InterfaceType 
  Max,
};

struct TreeExtendsInterfaces: public Tree {
  enum NTExtendsInterfacesVariants variant;
  TreeExtendsInterfaces* ExtendsInterfaces;
  TreeInterfaceType* InterfaceType;
};

enum class NTDimExprsVariants {
  DimExpr,  // DimExpr 
  DimExprsDimExpr,  // DimExprs DimExpr 
  Max,
};

struct TreeDimExprs: public Tree {
  enum NTDimExprsVariants variant;
  TreeDimExprs* DimExprs;
  TreeDimExpr* DimExpr;
};

enum class NTQualifiedNameVariants {
  NameDotIdentifier,  // Name . Identifier 
  Max,
};

struct TreeQualifiedName: public Tree {
  enum NTQualifiedNameVariants variant;
  TreeIdentifier* Identifier;
  TreeName* Name;
};

enum class NTInterfaceMemberDeclarationsVariants {
  InterfaceMemberDeclaration,  // InterfaceMemberDeclaration 
  InterfaceMemberDeclarationsInterfaceMemberDeclaration,  // InterfaceMemberDeclarations InterfaceMemberDeclaration 
  Max,
};

struct TreeInterfaceMemberDeclarations: public Tree {
  enum NTInterfaceMemberDeclarationsVariants variant;
  TreeInterfaceMemberDeclarations* InterfaceMemberDeclarations;
  TreeInterfaceMemberDeclaration* InterfaceMemberDeclaration;
};

enum class NTBlockStatementVariants {
  LocalVariableDeclarationStatement,  // LocalVariableDeclarationStatement 
  Statement,  // Statement 
  Max,
};

struct TreeBlockStatement: public Tree {
  enum NTBlockStatementVariants variant;
  TreeStatement* Statement;
  TreeLocalVariableDeclarationStatement* LocalVariableDeclarationStatement;
};

enum class NTWhileStatementNoShortIfVariants {
  WhileLParExpressionRParStatementNoShortIf,  // while ( Expression ) StatementNoShortIf 
  Max,
};

struct TreeWhileStatementNoShortIf: public Tree {
  enum NTWhileStatementNoShortIfVariants variant;
  TreeStatementNoShortIf* StatementNoShortIf;
  TreeExpression* Expression;
};

enum class NTInterfaceMemberDeclarationVariants {
  ConstantDeclaration,  // ConstantDeclaration 
  AbstractMethodDeclaration,  // AbstractMethodDeclaration 
  Max,
};

struct TreeInterfaceMemberDeclaration: public Tree {
  enum NTInterfaceMemberDeclarationVariants variant;
  TreeAbstractMethodDeclaration* AbstractMethodDeclaration;
  TreeConstantDeclaration* ConstantDeclaration;
};

enum class NTPostfixExpressionVariants {
  Primary,  // Primary 
  Name,  // Name 
  Max,
};

struct TreePostfixExpression: public Tree {
  enum NTPostfixExpressionVariants variant;
  TreeName* Name;
  TreePrimary* Primary;
};

enum class NTConstantDeclarationVariants {
  FieldDeclaration,  // FieldDeclaration 
  Max,
};

struct TreeConstantDeclaration: public Tree {
  enum NTConstantDeclarationVariants variant;
  TreeFieldDeclaration* FieldDeclaration;
};

enum class NTAbstractMethodDeclarationVariants {
  MethodHeaderSCol,  // MethodHeader ; 
  Max,
};

struct TreeAbstractMethodDeclaration: public Tree {
  enum NTAbstractMethodDeclarationVariants variant;
  TreeMethodHeader* MethodHeader;
};

enum class NTSuperVariants {
  extendsClassType,  // extends ClassType 
  Max,
};

struct TreeSuper: public Tree {
  enum NTSuperVariants variant;
  TreeClassType* ClassType;
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
  TreeVariableInitializers* VariableInitializers;
};

enum class NTReturnStatementVariants {
  ReturnSCol,  // return ; 
  ReturnExpressionSCol,  // return Expression ; 
  Max,
};

struct TreeReturnStatement: public Tree {
  enum NTReturnStatementVariants variant;
  TreeExpression* Expression;
};

enum class NTAdditiveExpressionVariants {
  MultiplicativeExpression,  // MultiplicativeExpression 
  AdditiveExpressionPlusMultiplicativeExpression,  // AdditiveExpression + MultiplicativeExpression 
  AdditiveExpressionMinusMultiplicativeExpression,  // AdditiveExpression - MultiplicativeExpression 
  Max,
};

struct TreeAdditiveExpression: public Tree {
  enum NTAdditiveExpressionVariants variant;
  TreeAdditiveExpression* AdditiveExpression;
  TreeMultiplicativeExpression* MultiplicativeExpression;
};

enum class NTVariableInitializersVariants {
  VariableInitializer,  // VariableInitializer 
  VariableInitializersComVariableInitializer,  // VariableInitializers , VariableInitializer 
  Max,
};

struct TreeVariableInitializers: public Tree {
  enum NTVariableInitializersVariants variant;
  TreeVariableInitializers* VariableInitializers;
  TreeVariableInitializer* VariableInitializer;
};

enum class NTTypeDeclarationsVariants {
  TypeDeclaration,  // TypeDeclaration 
  TypeDeclarationsTypeDeclaration,  // TypeDeclarations TypeDeclaration 
  Max,
};

struct TreeTypeDeclarations: public Tree {
  enum NTTypeDeclarationsVariants variant;
  TreeTypeDeclarations* TypeDeclarations;
  TreeTypeDeclaration* TypeDeclaration;
};

enum class NTLocalVariableDeclarationStatementVariants {
  LocalVariableDeclarationSCol,  // LocalVariableDeclaration ; 
  Max,
};

struct TreeLocalVariableDeclarationStatement: public Tree {
  enum NTLocalVariableDeclarationStatementVariants variant;
  TreeLocalVariableDeclaration* LocalVariableDeclaration;
};

enum class NTConstructorBodyVariants {
  LCBrRCBr,  // { } 
  LCBrBlockStatementsRCBr,  // { BlockStatements } 
  Max,
};

struct TreeConstructorBody: public Tree {
  enum NTConstructorBodyVariants variant;
  TreeBlockStatements* BlockStatements;
};

enum class NTLocalVariableDeclarationVariants {
  TypeVariableDeclarator,  // Type VariableDeclarator 
  Max,
};

struct TreeLocalVariableDeclaration: public Tree {
  enum NTLocalVariableDeclarationVariants variant;
  TreeVariableDeclarator* VariableDeclarator;
  TreeType* Type;
};

enum class NTStaticInitializerVariants {
  StaticBlock,  // static Block 
  Max,
};

struct TreeStaticInitializer: public Tree {
  enum NTStaticInitializerVariants variant;
  TreeBlock* Block;
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
  TreeForStatement* ForStatement;
  TreeIfThenElseStatement* IfThenElseStatement;
  TreeWhileStatement* WhileStatement;
  TreeStatementWithoutTrailingSubstatement* StatementWithoutTrailingSubstatement;
  TreeIfThenStatement* IfThenStatement;
};

enum class NTArrayAccessVariants {
  NameLSBrExpressionRSBr,  // Name [ Expression ] 
  PrimaryNoNewArrayLSBrExpressionRSBr,  // PrimaryNoNewArray [ Expression ] 
  Max,
};

struct TreeArrayAccess: public Tree {
  enum NTArrayAccessVariants variant;
  TreePrimaryNoNewArray* PrimaryNoNewArray;
  TreeName* Name;
  TreeExpression* Expression;
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
  TreeForStatementNoShortIf* ForStatementNoShortIf;
  TreeWhileStatementNoShortIf* WhileStatementNoShortIf;
  TreeStatementWithoutTrailingSubstatement* StatementWithoutTrailingSubstatement;
  TreeIfThenElseStatementNoShortIf* IfThenElseStatementNoShortIf;
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
  TreeExpressionStatement* ExpressionStatement;
  TreeBlock* Block;
  TreeReturnStatement* ReturnStatement;
  TreeEmptyStatement* EmptyStatement;
};

enum class NTEmptyStatementVariants {
  SCol,  // ; 
  Max,
};

struct TreeEmptyStatement: public Tree {
  enum NTEmptyStatementVariants variant;
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
  TreeForUpdate* ForUpdate;
  TreeExpression* Expression;
  TreeStatement* Statement;
  TreeForInit* ForInit;
};

enum class NTIfThenStatementVariants {
  IfLParExpressionRParStatement,  // if ( Expression ) Statement 
  Max,
};

struct TreeIfThenStatement: public Tree {
  enum NTIfThenStatementVariants variant;
  TreeStatement* Statement;
  TreeExpression* Expression;
};

enum class NTVariableDeclaratorIdVariants {
  Identifier,  // Identifier 
  VariableDeclaratorIdLSBrRSBr,  // VariableDeclaratorId [ ] 
  Max,
};

struct TreeVariableDeclaratorId: public Tree {
  enum NTVariableDeclaratorIdVariants variant;
  TreeVariableDeclaratorId* VariableDeclaratorId;
  TreeIdentifier* Identifier;
};

enum class NTArgumentListVariants {
  Expression,  // Expression 
  ArgumentListComExpression,  // ArgumentList , Expression 
  Max,
};

struct TreeArgumentList: public Tree {
  enum NTArgumentListVariants variant;
  TreeArgumentList* ArgumentList;
  TreeExpression* Expression;
};

enum class NTIfThenElseStatementVariants {
  IfLParExpressionRParStatementNoShortIfElseStatement,  // if ( Expression ) StatementNoShortIf else Statement 
  Max,
};

struct TreeIfThenElseStatement: public Tree {
  enum NTIfThenElseStatementVariants variant;
  TreeStatement* Statement;
  TreeExpression* Expression;
  TreeStatementNoShortIf* StatementNoShortIf;
};

enum class NTWhileStatementVariants {
  WhileLParExpressionRParStatement,  // while ( Expression ) Statement 
  Max,
};

struct TreeWhileStatement: public Tree {
  enum NTWhileStatementVariants variant;
  TreeStatement* Statement;
  TreeExpression* Expression;
};

enum class NTPrimaryVariants {
  PrimaryNoNewArray,  // PrimaryNoNewArray 
  ArrayCreationExpression,  // ArrayCreationExpression 
  Max,
};

struct TreePrimary: public Tree {
  enum NTPrimaryVariants variant;
  TreeArrayCreationExpression* ArrayCreationExpression;
  TreePrimaryNoNewArray* PrimaryNoNewArray;
};

enum class NTImportDeclarationVariants {
  SingleTypeImportDeclaration,  // SingleTypeImportDeclaration 
  TypeImportOnDemandDeclaration,  // TypeImportOnDemandDeclaration 
  Max,
};

struct TreeImportDeclaration: public Tree {
  enum NTImportDeclarationVariants variant;
  TreeTypeImportOnDemandDeclaration* TypeImportOnDemandDeclaration;
  TreeSingleTypeImportDeclaration* SingleTypeImportDeclaration;
};

enum class NTBlockVariants {
  LCBrRCBr,  // { } 
  LCBrBlockStatementsRCBr,  // { BlockStatements } 
  Max,
};

struct TreeBlock: public Tree {
  enum NTBlockVariants variant;
  TreeBlockStatements* BlockStatements;
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
  TreeForUpdate* ForUpdate;
  TreeExpression* Expression;
  TreeStatementNoShortIf* StatementNoShortIf;
  TreeForInit* ForInit;
};

enum class NTForInitVariants {
  StatementExpression,  // StatementExpression 
  LocalVariableDeclaration,  // LocalVariableDeclaration 
  Max,
};

struct TreeForInit: public Tree {
  enum NTForInitVariants variant;
  TreeLocalVariableDeclaration* LocalVariableDeclaration;
  TreeStatementExpression* StatementExpression;
};

enum class NTUnaryExpressionVariants {
  MinusUnaryExpression,  // - UnaryExpression 
  UnaryExpressionNotPlusMinus,  // UnaryExpressionNotPlusMinus 
  Max,
};

struct TreeUnaryExpression: public Tree {
  enum NTUnaryExpressionVariants variant;
  TreeUnaryExpressionNotPlusMinus* UnaryExpressionNotPlusMinus;
  TreeUnaryExpression* UnaryExpression;
};

enum class NTDimsVariants {
  LSBrRSBr,  // [ ] 
  DimsLSBrRSBr,  // Dims [ ] 
  Max,
};

struct TreeDims: public Tree {
  enum NTDimsVariants variant;
  TreeDims* Dims;
};

enum class NTBlockStatementsVariants {
  BlockStatement,  // BlockStatement 
  BlockStatementsBlockStatement,  // BlockStatements BlockStatement 
  Max,
};

struct TreeBlockStatements: public Tree {
  enum NTBlockStatementsVariants variant;
  TreeBlockStatements* BlockStatements;
  TreeBlockStatement* BlockStatement;
};

enum class NTFieldAccessVariants {
  PrimaryDotIdentifier,  // Primary . Identifier 
  Max,
};

struct TreeFieldAccess: public Tree {
  enum NTFieldAccessVariants variant;
  TreeIdentifier* Identifier;
  TreePrimary* Primary;
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
  TreeIdentifier* Identifier;
  TreePrimary* Primary;
  TreeName* Name;
  TreeArgumentList* ArgumentList;
};

enum class NTClassMemberDeclarationVariants {
  FieldDeclaration,  // FieldDeclaration 
  MethodDeclaration,  // MethodDeclaration 
  Max,
};

struct TreeClassMemberDeclaration: public Tree {
  enum NTClassMemberDeclarationVariants variant;
  TreeMethodDeclaration* MethodDeclaration;
  TreeFieldDeclaration* FieldDeclaration;
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
  TreeUnaryExpression* UnaryExpression;
  TreeName* Name;
  TreePrimitiveType* PrimitiveType;
  TreeDims* Dims;
  TreeUnaryExpressionNotPlusMinus* UnaryExpressionNotPlusMinus;
  TreeExpression* Expression;
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
  TreeMultiplicativeExpression* MultiplicativeExpression;
  TreeUnaryExpression* UnaryExpression;
};

enum class NTEqualityExpressionVariants {
  RelationalExpression,  // RelationalExpression 
  EqualityExpressionEqEqRelationalExpression,  // EqualityExpression == RelationalExpression 
  EqualityExpressionBangEqRelationalExpression,  // EqualityExpression != RelationalExpression 
  Max,
};

struct TreeEqualityExpression: public Tree {
  enum NTEqualityExpressionVariants variant;
  TreeEqualityExpression* EqualityExpression;
  TreeRelationalExpression* RelationalExpression;
};

enum class NTForUpdateVariants {
  StatementExpression,  // StatementExpression 
  Max,
};

struct TreeForUpdate: public Tree {
  enum NTForUpdateVariants variant;
  TreeStatementExpression* StatementExpression;
};

enum class NTConditionalAndExpressionVariants {
  EqualityExpression,  // EqualityExpression 
  ConditionalAndExpressionAmpAmpEqualityExpression,  // ConditionalAndExpression && EqualityExpression 
  Max,
};

struct TreeConditionalAndExpression: public Tree {
  enum NTConditionalAndExpressionVariants variant;
  TreeConditionalAndExpression* ConditionalAndExpression;
  TreeEqualityExpression* EqualityExpression;
};

} // namespace Parse 
