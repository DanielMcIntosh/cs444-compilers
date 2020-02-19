#pragma once
#include "parseTreeBase.h"
namespace Parse { 
enum class TAbstractMethodBodyV {
  SCol,  // ; 
  Max,
};

struct TAbstractMethodBody: public Tree {
  enum TAbstractMethodBodyV v;

  TAbstractMethodBody();
};

enum class TAbstractMethodDeclarationV {
  MethodHeaderSCol,  // MethodHeader ; 
  Max,
};

struct TAbstractMethodDeclaration: public Tree {
  enum TAbstractMethodDeclarationV v;
  TMethodHeader* methodHeader;

  TAbstractMethodDeclaration();
};

enum class TAdditiveExpressionV {
  MultiplicativeExpression,  // MultiplicativeExpression 
  AdditiveExpressionPlusMultiplicativeExpression,  // AdditiveExpression + MultiplicativeExpression 
  AdditiveExpressionMinusMultiplicativeExpression,  // AdditiveExpression - MultiplicativeExpression 
  Max,
};

struct TAdditiveExpression: public Tree {
  enum TAdditiveExpressionV v;
  TAdditiveExpression* additiveExpression;
  TMultiplicativeExpression* multiplicativeExpression;

  TAdditiveExpression();
};

enum class TAndExpressionV {
  EqualityExpression,  // EqualityExpression 
  AndExpressionAmpEqualityExpression,  // AndExpression & EqualityExpression 
  Max,
};

struct TAndExpression: public Tree {
  enum TAndExpressionV v;
  TAndExpression* andExpression;
  TEqualityExpression* equalityExpression;

  TAndExpression();
};

enum class TArgumentListV {
  Expression,  // Expression 
  ArgumentListComExpression,  // ArgumentList , Expression 
  Max,
};

struct TArgumentList: public Tree {
  enum TArgumentListV v;
  TArgumentList* argumentList;
  TExpression* expression;

  TArgumentList();
};

enum class TArrayAccessV {
  NameLSBrExpressionRSBr,  // Name [ Expression ] 
  PrimaryNoNewArrayLSBrExpressionRSBr,  // PrimaryNoNewArray [ Expression ] 
  Max,
};

struct TArrayAccess: public Tree {
  enum TArrayAccessV v;
  TPrimaryNoNewArray* primaryNoNewArray;
  TExpression* expression;
  TName* name;

  TArrayAccess();
};

enum class TArrayCreationExpressionV {
  NewPrimitiveTypeLSBrExpressionRSBr,  // new PrimitiveType [ Expression ] 
  NewClassOrInterfaceTypeLSBrExpressionRSBr,  // new ClassOrInterfaceType [ Expression ] 
  Max,
};

struct TArrayCreationExpression: public Tree {
  enum TArrayCreationExpressionV v;
  TClassOrInterfaceType* classOrInterfaceType;
  TExpression* expression;
  TPrimitiveType* primitiveType;

  TArrayCreationExpression();
};

enum class TArrayTypeV {
  PrimitiveTypeLSBrRSBr,  // PrimitiveType [ ] 
  NameLSBrRSBr,  // Name [ ] 
  Max,
};

struct TArrayType: public Tree {
  enum TArrayTypeV v;
  TName* name;
  TPrimitiveType* primitiveType;

  TArrayType();
};

enum class TAssignmentV {
  LeftHandSideEqAssignmentExpression,  // LeftHandSide = AssignmentExpression 
  Max,
};

struct TAssignment: public Tree {
  enum TAssignmentV v;
  TLeftHandSide* leftHandSide;
  TAssignmentExpression* assignmentExpression;

  TAssignment();
};

enum class TAssignmentExpressionV {
  ConditionalOrExpression,  // ConditionalOrExpression 
  Assignment,  // Assignment 
  Max,
};

struct TAssignmentExpression: public Tree {
  enum TAssignmentExpressionV v;
  TAssignment* assignment;
  TConditionalOrExpression* conditionalOrExpression;

  TAssignmentExpression();
};

enum class TBlockV {
  LCBrRCBr,  // { } 
  LCBrBlockStatementsRCBr,  // { BlockStatements } 
  Max,
};

struct TBlock: public Tree {
  enum TBlockV v;
  TBlockStatements* blockStatements;

  TBlock();
};

enum class TBlockStatementV {
  LocalVariableDeclarationStatement,  // LocalVariableDeclarationStatement 
  Statement,  // Statement 
  Max,
};

struct TBlockStatement: public Tree {
  enum TBlockStatementV v;
  TStatement* statement;
  TLocalVariableDeclarationStatement* localVariableDeclarationStatement;

  TBlockStatement();
};

enum class TBlockStatementsV {
  BlockStatement,  // BlockStatement 
  BlockStatementsBlockStatement,  // BlockStatements BlockStatement 
  Max,
};

struct TBlockStatements: public Tree {
  enum TBlockStatementsV v;
  TBlockStatements* blockStatements;
  TBlockStatement* blockStatement;

  TBlockStatements();
};

enum class TBooleanLiteralV {
  Max,
};

struct TBooleanLiteral: public Tree {
  enum TBooleanLiteralV v;
  bool value;

  TBooleanLiteral();
};

enum class TCastExpressionV {
  LParPrimitiveTypeRParUnaryExpression,  // ( PrimitiveType ) UnaryExpression 
  LParPrimitiveTypeLSBrRSBrRParUnaryExpression,  // ( PrimitiveType [ ] ) UnaryExpression 
  LParExpressionRParUnaryExpressionNotPlusMinus,  // ( Expression ) UnaryExpressionNotPlusMinus 
  LParNameLSBrRSBrRParUnaryExpressionNotPlusMinus,  // ( Name [ ] ) UnaryExpressionNotPlusMinus 
  Max,
};

struct TCastExpression: public Tree {
  enum TCastExpressionV v;
  TName* name;
  TExpression* expression;
  TUnaryExpression* unaryExpression;
  TUnaryExpressionNotPlusMinus* unaryExpressionNotPlusMinus;
  TPrimitiveType* primitiveType;

  TCastExpression();
};

enum class TCharacterLiteralV {
  Max,
};

struct TCharacterLiteral: public Tree {
  enum TCharacterLiteralV v;
  char value;

  TCharacterLiteral();
};

enum class TClassBodyV {
  LCBrRCBr,  // { } 
  LCBrClassMemberDeclarationsRCBr,  // { ClassMemberDeclarations } 
  Max,
};

struct TClassBody: public Tree {
  enum TClassBodyV v;
  TClassMemberDeclarations* classMemberDeclarations;

  TClassBody();
};

enum class TClassDeclarationV {
  ModifiersClassIdentifierClassBody,  // Modifiers class Identifier ClassBody 
  ModifiersClassIdentifierextendsClassTypeClassBody,  // Modifiers class Identifier extends ClassType ClassBody 
  ModifiersClassIdentifierimplementsInterfaceTypeListClassBody,  // Modifiers class Identifier implements InterfaceTypeList ClassBody 
  ModifiersClassIdentifierextendsClassTypeimplementsInterfaceTypeListClassBody,  // Modifiers class Identifier extends ClassType implements InterfaceTypeList ClassBody 
  Max,
};

struct TClassDeclaration: public Tree {
  enum TClassDeclarationV v;
  TClassType* classType;
  TInterfaceTypeList* interfaceTypeList;
  TIdentifier* identifier;
  TClassBody* classBody;
  TModifiers* modifiers;

  TClassDeclaration();
};

enum class TClassInstanceCreationExpressionV {
  NewClassTypeLParRPar,  // new ClassType ( ) 
  NewClassTypeLParArgumentListRPar,  // new ClassType ( ArgumentList ) 
  Max,
};

struct TClassInstanceCreationExpression: public Tree {
  enum TClassInstanceCreationExpressionV v;
  TArgumentList* argumentList;
  TClassType* classType;

  TClassInstanceCreationExpression();
};

enum class TClassMemberDeclarationV {
  FieldDeclaration,  // FieldDeclaration 
  MethodDeclaration,  // MethodDeclaration 
  ConstructorDeclaration,  // ConstructorDeclaration 
  Max,
};

struct TClassMemberDeclaration: public Tree {
  enum TClassMemberDeclarationV v;
  TConstructorDeclaration* constructorDeclaration;
  TFieldDeclaration* fieldDeclaration;
  TMethodDeclaration* methodDeclaration;

  TClassMemberDeclaration();
};

enum class TClassMemberDeclarationsV {
  ClassMemberDeclaration,  // ClassMemberDeclaration 
  ClassMemberDeclarationsClassMemberDeclaration,  // ClassMemberDeclarations ClassMemberDeclaration 
  Max,
};

struct TClassMemberDeclarations: public Tree {
  enum TClassMemberDeclarationsV v;
  TClassMemberDeclarations* classMemberDeclarations;
  TClassMemberDeclaration* classMemberDeclaration;

  TClassMemberDeclarations();
};

enum class TClassOrInterfaceTypeV {
  Name,  // Name 
  Max,
};

struct TClassOrInterfaceType: public Tree {
  enum TClassOrInterfaceTypeV v;
  TName* name;

  TClassOrInterfaceType();
};

enum class TClassTypeV {
  ClassOrInterfaceType,  // ClassOrInterfaceType 
  Max,
};

struct TClassType: public Tree {
  enum TClassTypeV v;
  TClassOrInterfaceType* classOrInterfaceType;

  TClassType();
};

enum class TCompilationUnitV {
  PackageDeclaration,  // PackageDeclaration 
  ImportDeclarations,  // ImportDeclarations 
  PackageDeclarationImportDeclarations,  // PackageDeclaration ImportDeclarations 
  TypeDeclaration,  // TypeDeclaration 
  PackageDeclarationTypeDeclaration,  // PackageDeclaration TypeDeclaration 
  ImportDeclarationsTypeDeclaration,  // ImportDeclarations TypeDeclaration 
  PackageDeclarationImportDeclarationsTypeDeclaration,  // PackageDeclaration ImportDeclarations TypeDeclaration 
  Max,
};

struct TCompilationUnit: public Tree {
  enum TCompilationUnitV v;
  TTypeDeclaration* typeDeclaration;
  TPackageDeclaration* packageDeclaration;
  TImportDeclarations* importDeclarations;

  TCompilationUnit();
};

enum class TConditionalAndExpressionV {
  InclusiveOrExpression,  // InclusiveOrExpression 
  ConditionalAndExpressionAmpAmpInclusiveOrExpression,  // ConditionalAndExpression && InclusiveOrExpression 
  Max,
};

struct TConditionalAndExpression: public Tree {
  enum TConditionalAndExpressionV v;
  TConditionalAndExpression* conditionalAndExpression;
  TInclusiveOrExpression* inclusiveOrExpression;

  TConditionalAndExpression();
};

enum class TConditionalOrExpressionV {
  ConditionalAndExpression,  // ConditionalAndExpression 
  ConditionalOrExpressionOrOrConditionalAndExpression,  // ConditionalOrExpression || ConditionalAndExpression 
  Max,
};

struct TConditionalOrExpression: public Tree {
  enum TConditionalOrExpressionV v;
  TConditionalOrExpression* conditionalOrExpression;
  TConditionalAndExpression* conditionalAndExpression;

  TConditionalOrExpression();
};

enum class TConstructorDeclarationV {
  ModifiersConstructorDeclaratorBlock,  // Modifiers ConstructorDeclarator Block 
  Max,
};

struct TConstructorDeclaration: public Tree {
  enum TConstructorDeclarationV v;
  TConstructorDeclarator* constructorDeclarator;
  TBlock* block;
  TModifiers* modifiers;

  TConstructorDeclaration();
};

enum class TConstructorDeclaratorV {
  IdentifierLParRPar,  // Identifier ( ) 
  IdentifierLParFormalParameterListRPar,  // Identifier ( FormalParameterList ) 
  Max,
};

struct TConstructorDeclarator: public Tree {
  enum TConstructorDeclaratorV v;
  TFormalParameterList* formalParameterList;
  TIdentifier* identifier;

  TConstructorDeclarator();
};

enum class TEqualityExpressionV {
  RelationalExpression,  // RelationalExpression 
  EqualityExpressionEqEqRelationalExpression,  // EqualityExpression == RelationalExpression 
  EqualityExpressionBangEqRelationalExpression,  // EqualityExpression != RelationalExpression 
  Max,
};

struct TEqualityExpression: public Tree {
  enum TEqualityExpressionV v;
  TEqualityExpression* equalityExpression;
  TRelationalExpression* relationalExpression;

  TEqualityExpression();
};

enum class TExpressionV {
  AssignmentExpression,  // AssignmentExpression 
  Max,
};

struct TExpression: public Tree {
  enum TExpressionV v;
  TAssignmentExpression* assignmentExpression;

  TExpression();
};

enum class TExpressionStatementV {
  SCol,  // ; 
  StatementExpressionSCol,  // StatementExpression ; 
  Max,
};

struct TExpressionStatement: public Tree {
  enum TExpressionStatementV v;
  TStatementExpression* statementExpression;

  TExpressionStatement();
};

enum class TExtendsInterfacesV {
  extendsInterfaceType,  // extends InterfaceType 
  ExtendsInterfacesComInterfaceType,  // ExtendsInterfaces , InterfaceType 
  Max,
};

struct TExtendsInterfaces: public Tree {
  enum TExtendsInterfacesV v;
  TExtendsInterfaces* extendsInterfaces;
  TInterfaceType* interfaceType;

  TExtendsInterfaces();
};

enum class TFieldAccessV {
  PrimaryDotIdentifier,  // Primary . Identifier 
  Max,
};

struct TFieldAccess: public Tree {
  enum TFieldAccessV v;
  TPrimary* primary;
  TIdentifier* identifier;

  TFieldAccess();
};

enum class TFieldDeclarationV {
  ModifiersTypeVariableDeclaratorSCol,  // Modifiers Type VariableDeclarator ; 
  Max,
};

struct TFieldDeclaration: public Tree {
  enum TFieldDeclarationV v;
  TType* type;
  TVariableDeclarator* variableDeclarator;
  TModifiers* modifiers;

  TFieldDeclaration();
};

enum class TForInitV {
  ExpressionStatement,  // ExpressionStatement 
  LocalVariableDeclarationStatement,  // LocalVariableDeclarationStatement 
  Max,
};

struct TForInit: public Tree {
  enum TForInitV v;
  TLocalVariableDeclarationStatement* localVariableDeclarationStatement;
  TExpressionStatement* expressionStatement;

  TForInit();
};

enum class TForStatementV {
  ForLParForInitSColRParStatement,  // for ( ForInit ; ) Statement 
  ForLParForInitExpressionSColRParStatement,  // for ( ForInit Expression ; ) Statement 
  ForLParForInitSColForUpdateRParStatement,  // for ( ForInit ; ForUpdate ) Statement 
  ForLParForInitExpressionSColForUpdateRParStatement,  // for ( ForInit Expression ; ForUpdate ) Statement 
  Max,
};

struct TForStatement: public Tree {
  enum TForStatementV v;
  TForUpdate* forUpdate;
  TExpression* expression;
  TStatement* statement;
  TForInit* forInit;

  TForStatement();
};

enum class TForStatementNoShortIfV {
  ForLParForInitSColRParStatementNoShortIf,  // for ( ForInit ; ) StatementNoShortIf 
  ForLParForInitExpressionSColRParStatementNoShortIf,  // for ( ForInit Expression ; ) StatementNoShortIf 
  ForLParForInitSColForUpdateRParStatementNoShortIf,  // for ( ForInit ; ForUpdate ) StatementNoShortIf 
  ForLParForInitExpressionSColForUpdateRParStatementNoShortIf,  // for ( ForInit Expression ; ForUpdate ) StatementNoShortIf 
  Max,
};

struct TForStatementNoShortIf: public Tree {
  enum TForStatementNoShortIfV v;
  TForUpdate* forUpdate;
  TExpression* expression;
  TStatementNoShortIf* statementNoShortIf;
  TForInit* forInit;

  TForStatementNoShortIf();
};

enum class TForUpdateV {
  StatementExpression,  // StatementExpression 
  Max,
};

struct TForUpdate: public Tree {
  enum TForUpdateV v;
  TStatementExpression* statementExpression;

  TForUpdate();
};

enum class TFormalParameterV {
  TypeIdentifier,  // Type Identifier 
  Max,
};

struct TFormalParameter: public Tree {
  enum TFormalParameterV v;
  TType* type;
  TIdentifier* identifier;

  TFormalParameter();
};

enum class TFormalParameterListV {
  FormalParameter,  // FormalParameter 
  FormalParameterListComFormalParameter,  // FormalParameterList , FormalParameter 
  Max,
};

struct TFormalParameterList: public Tree {
  enum TFormalParameterListV v;
  TFormalParameterList* formalParameterList;
  TFormalParameter* formalParameter;

  TFormalParameterList();
};

enum class TGoalV {
  BOFCompilationUnitEof,  // BOF CompilationUnit EOF 
  Max,
};

struct TGoal: public Tree {
  enum TGoalV v;
  TCompilationUnit* compilationUnit;

  TGoal();
};

enum class TIdentifierV {
  Max,
};

struct TIdentifier: public Tree {
  enum TIdentifierV v;
  string value;

  TIdentifier();
};

enum class TIfThenElseStatementV {
  IfLParExpressionRParStatementNoShortIfElseStatement,  // if ( Expression ) StatementNoShortIf else Statement 
  Max,
};

struct TIfThenElseStatement: public Tree {
  enum TIfThenElseStatementV v;
  TStatementNoShortIf* statementNoShortIf;
  TStatement* statement;
  TExpression* expression;

  TIfThenElseStatement();
};

enum class TIfThenElseStatementNoShortIfV {
  IfLParExpressionRParStatementNoShortIfElseStatementNoShortIf,  // if ( Expression ) StatementNoShortIf else StatementNoShortIf 
  Max,
};

struct TIfThenElseStatementNoShortIf: public Tree {
  enum TIfThenElseStatementNoShortIfV v;
  TExpression* expression;
  TStatementNoShortIf* statementNoShortIf;
  TStatementNoShortIf* statementNoShortIf2;

  TIfThenElseStatementNoShortIf();
};

enum class TIfThenStatementV {
  IfLParExpressionRParStatement,  // if ( Expression ) Statement 
  Max,
};

struct TIfThenStatement: public Tree {
  enum TIfThenStatementV v;
  TExpression* expression;
  TStatement* statement;

  TIfThenStatement();
};

enum class TImportDeclarationV {
  SingleTypeImportDeclaration,  // SingleTypeImportDeclaration 
  TypeImportOnDemandDeclaration,  // TypeImportOnDemandDeclaration 
  Max,
};

struct TImportDeclaration: public Tree {
  enum TImportDeclarationV v;
  TTypeImportOnDemandDeclaration* typeImportOnDemandDeclaration;
  TSingleTypeImportDeclaration* singleTypeImportDeclaration;

  TImportDeclaration();
};

enum class TImportDeclarationsV {
  ImportDeclaration,  // ImportDeclaration 
  ImportDeclarationsImportDeclaration,  // ImportDeclarations ImportDeclaration 
  Max,
};

struct TImportDeclarations: public Tree {
  enum TImportDeclarationsV v;
  TImportDeclarations* importDeclarations;
  TImportDeclaration* importDeclaration;

  TImportDeclarations();
};

enum class TInclusiveOrExpressionV {
  AndExpression,  // AndExpression 
  InclusiveOrExpressionOrAndExpression,  // InclusiveOrExpression | AndExpression 
  Max,
};

struct TInclusiveOrExpression: public Tree {
  enum TInclusiveOrExpressionV v;
  TInclusiveOrExpression* inclusiveOrExpression;
  TAndExpression* andExpression;

  TInclusiveOrExpression();
};

enum class TIntegerLiteralV {
  Max,
};

struct TIntegerLiteral: public Tree {
  enum TIntegerLiteralV v;
  unsigned int value;

  TIntegerLiteral();
};

enum class TInterfaceBodyV {
  LCBrRCBr,  // { } 
  LCBrInterfaceMemberDeclarationsRCBr,  // { InterfaceMemberDeclarations } 
  Max,
};

struct TInterfaceBody: public Tree {
  enum TInterfaceBodyV v;
  TInterfaceMemberDeclarations* interfaceMemberDeclarations;

  TInterfaceBody();
};

enum class TInterfaceDeclarationV {
  interfaceIdentifierInterfaceBody,  // interface Identifier InterfaceBody 
  ModifiersinterfaceIdentifierInterfaceBody,  // Modifiers interface Identifier InterfaceBody 
  interfaceIdentifierExtendsInterfacesInterfaceBody,  // interface Identifier ExtendsInterfaces InterfaceBody 
  ModifiersinterfaceIdentifierExtendsInterfacesInterfaceBody,  // Modifiers interface Identifier ExtendsInterfaces InterfaceBody 
  Max,
};

struct TInterfaceDeclaration: public Tree {
  enum TInterfaceDeclarationV v;
  TExtendsInterfaces* extendsInterfaces;
  TModifiers* modifiers;
  TInterfaceBody* interfaceBody;
  TIdentifier* identifier;

  TInterfaceDeclaration();
};

enum class TInterfaceMemberDeclarationV {
  AbstractMethodDeclaration,  // AbstractMethodDeclaration 
  Max,
};

struct TInterfaceMemberDeclaration: public Tree {
  enum TInterfaceMemberDeclarationV v;
  TAbstractMethodDeclaration* abstractMethodDeclaration;

  TInterfaceMemberDeclaration();
};

enum class TInterfaceMemberDeclarationsV {
  InterfaceMemberDeclaration,  // InterfaceMemberDeclaration 
  InterfaceMemberDeclarationsInterfaceMemberDeclaration,  // InterfaceMemberDeclarations InterfaceMemberDeclaration 
  Max,
};

struct TInterfaceMemberDeclarations: public Tree {
  enum TInterfaceMemberDeclarationsV v;
  TInterfaceMemberDeclarations* interfaceMemberDeclarations;
  TInterfaceMemberDeclaration* interfaceMemberDeclaration;

  TInterfaceMemberDeclarations();
};

enum class TInterfaceTypeV {
  ClassOrInterfaceType,  // ClassOrInterfaceType 
  Max,
};

struct TInterfaceType: public Tree {
  enum TInterfaceTypeV v;
  TClassOrInterfaceType* classOrInterfaceType;

  TInterfaceType();
};

enum class TInterfaceTypeListV {
  InterfaceType,  // InterfaceType 
  InterfaceTypeListComInterfaceType,  // InterfaceTypeList , InterfaceType 
  Max,
};

struct TInterfaceTypeList: public Tree {
  enum TInterfaceTypeListV v;
  TInterfaceTypeList* interfaceTypeList;
  TInterfaceType* interfaceType;

  TInterfaceTypeList();
};

enum class TLeftHandSideV {
  Name,  // Name 
  FieldAccess,  // FieldAccess 
  ArrayAccess,  // ArrayAccess 
  Max,
};

struct TLeftHandSide: public Tree {
  enum TLeftHandSideV v;
  TName* name;
  TArrayAccess* arrayAccess;
  TFieldAccess* fieldAccess;

  TLeftHandSide();
};

enum class TLiteralV {
  IntegerLiteral,  // IntegerLiteral 
  BooleanLiteral,  // BooleanLiteral 
  CharacterLiteral,  // CharacterLiteral 
  StringLiteral,  // StringLiteral 
  NullLiteral,  // NullLiteral 
  Max,
};

struct TLiteral: public Tree {
  enum TLiteralV v;
  TNullLiteral* nullLiteral;
  TCharacterLiteral* characterLiteral;
  TIntegerLiteral* integerLiteral;
  TStringLiteral* stringLiteral;
  TBooleanLiteral* booleanLiteral;

  TLiteral();
};

enum class TLocalVariableDeclarationV {
  TypeVariableDeclarator,  // Type VariableDeclarator 
  Max,
};

struct TLocalVariableDeclaration: public Tree {
  enum TLocalVariableDeclarationV v;
  TType* type;
  TVariableDeclarator* variableDeclarator;

  TLocalVariableDeclaration();
};

enum class TLocalVariableDeclarationStatementV {
  LocalVariableDeclarationSCol,  // LocalVariableDeclaration ; 
  Max,
};

struct TLocalVariableDeclarationStatement: public Tree {
  enum TLocalVariableDeclarationStatementV v;
  TLocalVariableDeclaration* localVariableDeclaration;

  TLocalVariableDeclarationStatement();
};

enum class TMethodBodyV {
  Block,  // Block 
  AbstractMethodBody,  // AbstractMethodBody 
  Max,
};

struct TMethodBody: public Tree {
  enum TMethodBodyV v;
  TAbstractMethodBody* abstractMethodBody;
  TBlock* block;

  TMethodBody();
};

enum class TMethodDeclarationV {
  MethodHeaderMethodBody,  // MethodHeader MethodBody 
  Max,
};

struct TMethodDeclaration: public Tree {
  enum TMethodDeclarationV v;
  TMethodHeader* methodHeader;
  TMethodBody* methodBody;

  TMethodDeclaration();
};

enum class TMethodDeclaratorV {
  IdentifierLParRPar,  // Identifier ( ) 
  IdentifierLParFormalParameterListRPar,  // Identifier ( FormalParameterList ) 
  Max,
};

struct TMethodDeclarator: public Tree {
  enum TMethodDeclaratorV v;
  TFormalParameterList* formalParameterList;
  TIdentifier* identifier;

  TMethodDeclarator();
};

enum class TMethodHeaderV {
  TypeMethodDeclarator,  // Type MethodDeclarator 
  ModifiersTypeMethodDeclarator,  // Modifiers Type MethodDeclarator 
  VoidMethodDeclarator,  // void MethodDeclarator 
  ModifiersVoidMethodDeclarator,  // Modifiers void MethodDeclarator 
  Max,
};

struct TMethodHeader: public Tree {
  enum TMethodHeaderV v;
  TModifiers* modifiers;
  TMethodDeclarator* methodDeclarator;
  TType* type;

  TMethodHeader();
};

enum class TMethodInvocationV {
  NameLParRPar,  // Name ( ) 
  NameLParArgumentListRPar,  // Name ( ArgumentList ) 
  PrimaryDotIdentifierLParRPar,  // Primary . Identifier ( ) 
  PrimaryDotIdentifierLParArgumentListRPar,  // Primary . Identifier ( ArgumentList ) 
  Max,
};

struct TMethodInvocation: public Tree {
  enum TMethodInvocationV v;
  TIdentifier* identifier;
  TPrimary* primary;
  TName* name;
  TArgumentList* argumentList;

  TMethodInvocation();
};

enum class TModifierV {
  Public,  // public 
  Protected,  // protected 
  Static,  // static 
  abstract,  // abstract 
  final,  // final 
  native,  // native 
  Max,
};

struct TModifier: public Tree {
  enum TModifierV v;

  TModifier();
};

enum class TModifiersV {
  Modifier,  // Modifier 
  ModifiersModifier,  // Modifiers Modifier 
  Max,
};

struct TModifiers: public Tree {
  enum TModifiersV v;
  TModifiers* modifiers;
  TModifier* modifier;

  TModifiers();
};

enum class TMultiplicativeExpressionV {
  UnaryExpression,  // UnaryExpression 
  MultiplicativeExpressionStarUnaryExpression,  // MultiplicativeExpression * UnaryExpression 
  MultiplicativeExpressionRSlashUnaryExpression,  // MultiplicativeExpression / UnaryExpression 
  MultiplicativeExpressionPercUnaryExpression,  // MultiplicativeExpression % UnaryExpression 
  Max,
};

struct TMultiplicativeExpression: public Tree {
  enum TMultiplicativeExpressionV v;
  TMultiplicativeExpression* multiplicativeExpression;
  TUnaryExpression* unaryExpression;

  TMultiplicativeExpression();
};

enum class TNameV {
  Identifier,  // Identifier 
  NameDotIdentifier,  // Name . Identifier 
  Max,
};

struct TName: public Tree {
  enum TNameV v;
  TName* name;
  TIdentifier* identifier;

  TName();
};

enum class TNullLiteralV {
  Max,
};

struct TNullLiteral: public Tree {
  enum TNullLiteralV v;
  bool value;

  TNullLiteral();
};

enum class TPackageDeclarationV {
  packageNameSCol,  // package Name ; 
  Max,
};

struct TPackageDeclaration: public Tree {
  enum TPackageDeclarationV v;
  TName* name;

  TPackageDeclaration();
};

enum class TParenthesizedExpressionV {
  LParExpressionRPar,  // ( Expression ) 
  Max,
};

struct TParenthesizedExpression: public Tree {
  enum TParenthesizedExpressionV v;
  TExpression* expression;

  TParenthesizedExpression();
};

enum class TPrimaryV {
  PrimaryNoNewArray,  // PrimaryNoNewArray 
  ArrayCreationExpression,  // ArrayCreationExpression 
  Max,
};

struct TPrimary: public Tree {
  enum TPrimaryV v;
  TArrayCreationExpression* arrayCreationExpression;
  TPrimaryNoNewArray* primaryNoNewArray;

  TPrimary();
};

enum class TPrimaryNoNewArrayV {
  Literal,  // Literal 
  This2,  // This2 
  ParenthesizedExpression,  // ParenthesizedExpression 
  ClassInstanceCreationExpression,  // ClassInstanceCreationExpression 
  FieldAccess,  // FieldAccess 
  MethodInvocation,  // MethodInvocation 
  ArrayAccess,  // ArrayAccess 
  Max,
};

struct TPrimaryNoNewArray: public Tree {
  enum TPrimaryNoNewArrayV v;
  TMethodInvocation* methodInvocation;
  TThis2* this2;
  TLiteral* literal;
  TArrayAccess* arrayAccess;
  TParenthesizedExpression* parenthesizedExpression;
  TClassInstanceCreationExpression* classInstanceCreationExpression;
  TFieldAccess* fieldAccess;

  TPrimaryNoNewArray();
};

enum class TPrimitiveTypeV {
  boolean,  // boolean 
  byte,  // byte 
  Short,  // short 
  Int,  // int 
  Char,  // char 
  Max,
};

struct TPrimitiveType: public Tree {
  enum TPrimitiveTypeV v;

  TPrimitiveType();
};

enum class TReferenceTypeV {
  ClassOrInterfaceType,  // ClassOrInterfaceType 
  ArrayType,  // ArrayType 
  Max,
};

struct TReferenceType: public Tree {
  enum TReferenceTypeV v;
  TArrayType* arrayType;
  TClassOrInterfaceType* classOrInterfaceType;

  TReferenceType();
};

enum class TRelationalExpressionV {
  AdditiveExpression,  // AdditiveExpression 
  RelationalExpressionLeAdditiveExpression,  // RelationalExpression < AdditiveExpression 
  RelationalExpressionGrAdditiveExpression,  // RelationalExpression > AdditiveExpression 
  RelationalExpressionLeEqAdditiveExpression,  // RelationalExpression <= AdditiveExpression 
  RelationalExpressionGrEqAdditiveExpression,  // RelationalExpression >= AdditiveExpression 
  RelationalExpressioninstanceofReferenceType,  // RelationalExpression instanceof ReferenceType 
  Max,
};

struct TRelationalExpression: public Tree {
  enum TRelationalExpressionV v;
  TReferenceType* referenceType;
  TAdditiveExpression* additiveExpression;
  TRelationalExpression* relationalExpression;

  TRelationalExpression();
};

enum class TReturnStatementV {
  ReturnSCol,  // return ; 
  ReturnExpressionSCol,  // return Expression ; 
  Max,
};

struct TReturnStatement: public Tree {
  enum TReturnStatementV v;
  TExpression* expression;

  TReturnStatement();
};

enum class TSingleTypeImportDeclarationV {
  importNameSCol,  // import Name ; 
  Max,
};

struct TSingleTypeImportDeclaration: public Tree {
  enum TSingleTypeImportDeclarationV v;
  TName* name;

  TSingleTypeImportDeclaration();
};

enum class TStatementV {
  StatementWithoutTrailingSubstatement,  // StatementWithoutTrailingSubstatement 
  IfThenStatement,  // IfThenStatement 
  IfThenElseStatement,  // IfThenElseStatement 
  WhileStatement,  // WhileStatement 
  ForStatement,  // ForStatement 
  Max,
};

struct TStatement: public Tree {
  enum TStatementV v;
  TForStatement* forStatement;
  TIfThenElseStatement* ifThenElseStatement;
  TWhileStatement* whileStatement;
  TStatementWithoutTrailingSubstatement* statementWithoutTrailingSubstatement;
  TIfThenStatement* ifThenStatement;

  TStatement();
};

enum class TStatementExpressionV {
  Assignment,  // Assignment 
  MethodInvocation,  // MethodInvocation 
  ClassInstanceCreationExpression,  // ClassInstanceCreationExpression 
  Max,
};

struct TStatementExpression: public Tree {
  enum TStatementExpressionV v;
  TClassInstanceCreationExpression* classInstanceCreationExpression;
  TAssignment* assignment;
  TMethodInvocation* methodInvocation;

  TStatementExpression();
};

enum class TStatementNoShortIfV {
  StatementWithoutTrailingSubstatement,  // StatementWithoutTrailingSubstatement 
  IfThenElseStatementNoShortIf,  // IfThenElseStatementNoShortIf 
  WhileStatementNoShortIf,  // WhileStatementNoShortIf 
  ForStatementNoShortIf,  // ForStatementNoShortIf 
  Max,
};

struct TStatementNoShortIf: public Tree {
  enum TStatementNoShortIfV v;
  TForStatementNoShortIf* forStatementNoShortIf;
  TWhileStatementNoShortIf* whileStatementNoShortIf;
  TStatementWithoutTrailingSubstatement* statementWithoutTrailingSubstatement;
  TIfThenElseStatementNoShortIf* ifThenElseStatementNoShortIf;

  TStatementNoShortIf();
};

enum class TStatementWithoutTrailingSubstatementV {
  Block,  // Block 
  ExpressionStatement,  // ExpressionStatement 
  ReturnStatement,  // ReturnStatement 
  Max,
};

struct TStatementWithoutTrailingSubstatement: public Tree {
  enum TStatementWithoutTrailingSubstatementV v;
  TReturnStatement* returnStatement;
  TBlock* block;
  TExpressionStatement* expressionStatement;

  TStatementWithoutTrailingSubstatement();
};

enum class TStringLiteralV {
  Max,
};

struct TStringLiteral: public Tree {
  enum TStringLiteralV v;
  string value;

  TStringLiteral();
};

enum class TThis2V {
  This2,  // this 
  Max,
};

struct TThis2: public Tree {
  enum TThis2V v;

  TThis2();
};

enum class TTypeV {
  PrimitiveType,  // PrimitiveType 
  ReferenceType,  // ReferenceType 
  Max,
};

struct TType: public Tree {
  enum TTypeV v;
  TReferenceType* referenceType;
  TPrimitiveType* primitiveType;

  TType();
};

enum class TTypeDeclarationV {
  ClassDeclaration,  // ClassDeclaration 
  InterfaceDeclaration,  // InterfaceDeclaration 
  SCol,  // ; 
  Max,
};

struct TTypeDeclaration: public Tree {
  enum TTypeDeclarationV v;
  TInterfaceDeclaration* interfaceDeclaration;
  TClassDeclaration* classDeclaration;

  TTypeDeclaration();
};

enum class TTypeImportOnDemandDeclarationV {
  importNameDotStarSCol,  // import Name . * ; 
  Max,
};

struct TTypeImportOnDemandDeclaration: public Tree {
  enum TTypeImportOnDemandDeclarationV v;
  TName* name;

  TTypeImportOnDemandDeclaration();
};

enum class TUnaryExpressionV {
  MinusUnaryExpression,  // - UnaryExpression 
  UnaryExpressionNotPlusMinus,  // UnaryExpressionNotPlusMinus 
  Max,
};

struct TUnaryExpression: public Tree {
  enum TUnaryExpressionV v;
  TUnaryExpressionNotPlusMinus* unaryExpressionNotPlusMinus;
  TUnaryExpression* unaryExpression;

  TUnaryExpression();
};

enum class TUnaryExpressionNotPlusMinusV {
  Primary,  // Primary 
  Name,  // Name 
  BangUnaryExpression,  // ! UnaryExpression 
  CastExpression,  // CastExpression 
  Max,
};

struct TUnaryExpressionNotPlusMinus: public Tree {
  enum TUnaryExpressionNotPlusMinusV v;
  TCastExpression* castExpression;
  TUnaryExpression* unaryExpression;
  TPrimary* primary;
  TName* name;

  TUnaryExpressionNotPlusMinus();
};

enum class TVariableDeclaratorV {
  Identifier,  // Identifier 
  IdentifierEqExpression,  // Identifier = Expression 
  Max,
};

struct TVariableDeclarator: public Tree {
  enum TVariableDeclaratorV v;
  TExpression* expression;
  TIdentifier* identifier;

  TVariableDeclarator();
};

enum class TWhileStatementV {
  WhileLParExpressionRParStatement,  // while ( Expression ) Statement 
  Max,
};

struct TWhileStatement: public Tree {
  enum TWhileStatementV v;
  TExpression* expression;
  TStatement* statement;

  TWhileStatement();
};

enum class TWhileStatementNoShortIfV {
  WhileLParExpressionRParStatementNoShortIf,  // while ( Expression ) StatementNoShortIf 
  Max,
};

struct TWhileStatementNoShortIf: public Tree {
  enum TWhileStatementNoShortIfV v;
  TExpression* expression;
  TStatementNoShortIf* statementNoShortIf;

  TWhileStatementNoShortIf();
};

} // namespace Parse 
