#pragma once
#include "parserASTBase.h"
#ifndef PARSERAST_DISABLED
namespace Parse { 
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

enum class NTConditionalAndExpressionVariants {
  InclusiveOrExpression,  // InclusiveOrExpression 
  ConditionalAndExpressionAmpAmpEqualityExpression,  // ConditionalAndExpression && EqualityExpression 
  Max,
};

struct TreeConditionalAndExpression: public Tree {
  enum NTConditionalAndExpressionVariants variant;
  TreeEqualityExpression* equalityExpression;
  TreeInclusiveOrExpression* inclusiveOrExpression;
  TreeConditionalAndExpression* conditionalAndExpression;

  TreeConditionalAndExpression(): Tree(NonTerminalType::ConditionalAndExpression), variant(NTConditionalAndExpressionVariants::Max), equalityExpression(nullptr) , inclusiveOrExpression(nullptr) , conditionalAndExpression(nullptr) {

  }
};

enum class NTAndExpressionVariants {
  EqualityExpression,  // EqualityExpression 
  AndExpressionAmpEqualityExpression,  // AndExpression & EqualityExpression 
  Max,
};

struct TreeAndExpression: public Tree {
  enum NTAndExpressionVariants variant;
  TreeAndExpression* andExpression;
  TreeEqualityExpression* equalityExpression;

  TreeAndExpression(): Tree(NonTerminalType::AndExpression), variant(NTAndExpressionVariants::Max), andExpression(nullptr) , equalityExpression(nullptr) {

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

enum class NTCastExpressionVariants {
  LParPrimitiveTypeRParUnaryExpression,  // ( PrimitiveType ) UnaryExpression 
  LParPrimitiveTypeLSBrRSBrRParUnaryExpression,  // ( PrimitiveType [ ] ) UnaryExpression 
  LParExpressionRParUnaryExpressionNotPlusMinus,  // ( Expression ) UnaryExpressionNotPlusMinus 
  LParNameLSBrRSBrRParUnaryExpressionNotPlusMinus,  // ( Name [ ] ) UnaryExpressionNotPlusMinus 
  Max,
};

struct TreeCastExpression: public Tree {
  enum NTCastExpressionVariants variant;
  TreeName* name;
  TreeExpression* expression;
  TreeUnaryExpressionNotPlusMinus* unaryExpressionNotPlusMinus;
  TreePrimitiveType* primitiveType;
  TreeUnaryExpression* unaryExpression;

  TreeCastExpression(): Tree(NonTerminalType::CastExpression), variant(NTCastExpressionVariants::Max), name(nullptr) , expression(nullptr) , unaryExpressionNotPlusMinus(nullptr) , primitiveType(nullptr) , unaryExpression(nullptr) {

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

enum class NTParenthesizedExpressionVariants {
  LParExpressionRPar,  // ( Expression ) 
  Max,
};

struct TreeParenthesizedExpression: public Tree {
  enum NTParenthesizedExpressionVariants variant;
  TreeExpression* expression;

  TreeParenthesizedExpression(): Tree(NonTerminalType::ParenthesizedExpression), variant(NTParenthesizedExpressionVariants::Max), expression(nullptr) {

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

enum class NTForInitVariants {
  ExpressionStatement,  // ExpressionStatement 
  LocalVariableDeclarationStatement,  // LocalVariableDeclarationStatement 
  Max,
};

struct TreeForInit: public Tree {
  enum NTForInitVariants variant;
  TreeLocalVariableDeclarationStatement* localVariableDeclarationStatement;
  TreeExpressionStatement* expressionStatement;

  TreeForInit(): Tree(NonTerminalType::ForInit), variant(NTForInitVariants::Max), localVariableDeclarationStatement(nullptr) , expressionStatement(nullptr) {

  }
};

enum class NTForStatementVariants {
  ForLParForInitSColRParStatement,  // for ( ForInit ; ) Statement 
  ForLParForInitExpressionSColRParStatement,  // for ( ForInit Expression ; ) Statement 
  ForLParForInitSColForUpdateRParStatement,  // for ( ForInit ; ForUpdate ) Statement 
  ForLParForInitExpressionSColForUpdateRParStatement,  // for ( ForInit Expression ; ForUpdate ) Statement 
  Max,
};

struct TreeForStatement: public Tree {
  enum NTForStatementVariants variant;
  TreeForUpdate* forUpdate;
  TreeExpression* expression;
  TreeForInit* forInit;
  TreeStatement* statement;

  TreeForStatement(): Tree(NonTerminalType::ForStatement), variant(NTForStatementVariants::Max), forUpdate(nullptr) , expression(nullptr) , forInit(nullptr) , statement(nullptr) {

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

enum class NTClassMemberDeclarationVariants {
  FieldDeclaration,  // FieldDeclaration 
  MethodDeclaration,  // MethodDeclaration 
  ConstructorDeclaration,  // ConstructorDeclaration 
  Max,
};

struct TreeClassMemberDeclaration: public Tree {
  enum NTClassMemberDeclarationVariants variant;
  TreeConstructorDeclaration* constructorDeclaration;
  TreeFieldDeclaration* fieldDeclaration;
  TreeMethodDeclaration* methodDeclaration;

  TreeClassMemberDeclaration(): Tree(NonTerminalType::ClassMemberDeclaration), variant(NTClassMemberDeclarationVariants::Max), constructorDeclaration(nullptr) , fieldDeclaration(nullptr) , methodDeclaration(nullptr) {

  }
};

enum class NTIntegerLiteralVariants {
  Max,
};

struct TreeIntegerLiteral: public Tree {
  enum NTIntegerLiteralVariants variant;
  int value;

  TreeIntegerLiteral(): Tree(NonTerminalType::IntegerLiteral), variant(NTIntegerLiteralVariants::Max){

  }
};

enum class NTArrayTypeVariants {
  PrimitiveTypeLSBrRSBr,  // PrimitiveType [ ] 
  NameLSBrRSBr,  // Name [ ] 
  Max,
};

struct TreeArrayType: public Tree {
  enum NTArrayTypeVariants variant;
  TreeName* name;
  TreePrimitiveType* primitiveType;

  TreeArrayType(): Tree(NonTerminalType::ArrayType), variant(NTArrayTypeVariants::Max), name(nullptr) , primitiveType(nullptr) {

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

enum class NTNullLiteralVariants {
  Max,
};

struct TreeNullLiteral: public Tree {
  enum NTNullLiteralVariants variant;
  bool value;

  TreeNullLiteral(): Tree(NonTerminalType::NullLiteral), variant(NTNullLiteralVariants::Max){

  }
};

enum class NTExpressionStatementVariants {
  SCol,  // ; 
  StatementExpressionSCol,  // StatementExpression ; 
  Max,
};

struct TreeExpressionStatement: public Tree {
  enum NTExpressionStatementVariants variant;
  TreeStatementExpression* statementExpression;

  TreeExpressionStatement(): Tree(NonTerminalType::ExpressionStatement), variant(NTExpressionStatementVariants::Max), statementExpression(nullptr) {

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

enum class NTArrayCreationExpressionVariants {
  NewPrimitiveTypeLSBrExpressionRSBr,  // new PrimitiveType [ Expression ] 
  NewClassOrInterfaceTypeLSBrExpressionRSBr,  // new ClassOrInterfaceType [ Expression ] 
  Max,
};

struct TreeArrayCreationExpression: public Tree {
  enum NTArrayCreationExpressionVariants variant;
  TreeClassOrInterfaceType* classOrInterfaceType;
  TreePrimitiveType* primitiveType;
  TreeExpression* expression;

  TreeArrayCreationExpression(): Tree(NonTerminalType::ArrayCreationExpression), variant(NTArrayCreationExpressionVariants::Max), classOrInterfaceType(nullptr) , primitiveType(nullptr) , expression(nullptr) {

  }
};

enum class NTNameVariants {
  Identifier,  // Identifier 
  NameDotIdentifier,  // Name . Identifier 
  Max,
};

struct TreeName: public Tree {
  enum NTNameVariants variant;
  TreeName* name;
  TreeIdentifier* identifier;

  TreeName(): Tree(NonTerminalType::Name), variant(NTNameVariants::Max), name(nullptr) , identifier(nullptr) {

  }
};

enum class NTClassBodyVariants {
  LCBrRCBr,  // { } 
  LCBrClassMemberDeclarationsRCBr,  // { ClassMemberDeclarations } 
  Max,
};

struct TreeClassBody: public Tree {
  enum NTClassBodyVariants variant;
  TreeClassMemberDeclarations* classMemberDeclarations;

  TreeClassBody(): Tree(NonTerminalType::ClassBody), variant(NTClassBodyVariants::Max), classMemberDeclarations(nullptr) {

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

enum class NTCompilationUnitVariants {
  PackageDeclaration,  // PackageDeclaration 
  ImportDeclarations,  // ImportDeclarations 
  PackageDeclarationImportDeclarations,  // PackageDeclaration ImportDeclarations 
  TypeDeclaration,  // TypeDeclaration 
  PackageDeclarationTypeDeclaration,  // PackageDeclaration TypeDeclaration 
  ImportDeclarationsTypeDeclaration,  // ImportDeclarations TypeDeclaration 
  PackageDeclarationImportDeclarationsTypeDeclaration,  // PackageDeclaration ImportDeclarations TypeDeclaration 
  Max,
};

struct TreeCompilationUnit: public Tree {
  enum NTCompilationUnitVariants variant;
  TreeTypeDeclaration* typeDeclaration;
  TreePackageDeclaration* packageDeclaration;
  TreeImportDeclarations* importDeclarations;

  TreeCompilationUnit(): Tree(NonTerminalType::CompilationUnit), variant(NTCompilationUnitVariants::Max), typeDeclaration(nullptr) , packageDeclaration(nullptr) , importDeclarations(nullptr) {

  }
};

enum class NTForStatementNoShortIfVariants {
  ForLParForInitSColRParStatementNoShortIf,  // for ( ForInit ; ) StatementNoShortIf 
  ForLParForInitExpressionSColRParStatementNoShortIf,  // for ( ForInit Expression ; ) StatementNoShortIf 
  ForLParForInitSColForUpdateRParStatementNoShortIf,  // for ( ForInit ; ForUpdate ) StatementNoShortIf 
  ForLParForInitExpressionSColForUpdateRParStatementNoShortIf,  // for ( ForInit Expression ; ForUpdate ) StatementNoShortIf 
  Max,
};

struct TreeForStatementNoShortIf: public Tree {
  enum NTForStatementNoShortIfVariants variant;
  TreeForUpdate* forUpdate;
  TreeExpression* expression;
  TreeForInit* forInit;
  TreeStatementNoShortIf* statementNoShortIf;

  TreeForStatementNoShortIf(): Tree(NonTerminalType::ForStatementNoShortIf), variant(NTForStatementNoShortIfVariants::Max), forUpdate(nullptr) , expression(nullptr) , forInit(nullptr) , statementNoShortIf(nullptr) {

  }
};

enum class NTCharacterLiteralVariants {
  Max,
};

struct TreeCharacterLiteral: public Tree {
  enum NTCharacterLiteralVariants variant;
  char value;

  TreeCharacterLiteral(): Tree(NonTerminalType::CharacterLiteral), variant(NTCharacterLiteralVariants::Max){

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

enum class NTInclusiveOrExpressionVariants {
  AndExpression,  // AndExpression 
  InclusiveOrExpressionOrAndExpression,  // InclusiveOrExpression | AndExpression 
  Max,
};

struct TreeInclusiveOrExpression: public Tree {
  enum NTInclusiveOrExpressionVariants variant;
  TreeInclusiveOrExpression* inclusiveOrExpression;
  TreeAndExpression* andExpression;

  TreeInclusiveOrExpression(): Tree(NonTerminalType::InclusiveOrExpression), variant(NTInclusiveOrExpressionVariants::Max), inclusiveOrExpression(nullptr) , andExpression(nullptr) {

  }
};

enum class NTStatementWithoutTrailingSubstatementVariants {
  Block,  // Block 
  ExpressionStatement,  // ExpressionStatement 
  ReturnStatement,  // ReturnStatement 
  Max,
};

struct TreeStatementWithoutTrailingSubstatement: public Tree {
  enum NTStatementWithoutTrailingSubstatementVariants variant;
  TreeReturnStatement* returnStatement;
  TreeBlock* block;
  TreeExpressionStatement* expressionStatement;

  TreeStatementWithoutTrailingSubstatement(): Tree(NonTerminalType::StatementWithoutTrailingSubstatement), variant(NTStatementWithoutTrailingSubstatementVariants::Max), returnStatement(nullptr) , block(nullptr) , expressionStatement(nullptr) {

  }
};

enum class NTIdentifierVariants {
  Max,
};

struct TreeIdentifier: public Tree {
  enum NTIdentifierVariants variant;
  string value;

  TreeIdentifier(): Tree(NonTerminalType::Identifier), variant(NTIdentifierVariants::Max){

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

enum class NTStringLiteralVariants {
  Max,
};

struct TreeStringLiteral: public Tree {
  enum NTStringLiteralVariants variant;
  string value;

  TreeStringLiteral(): Tree(NonTerminalType::StringLiteral), variant(NTStringLiteralVariants::Max){

  }
};

enum class NTPrimitiveTypeVariants {
  boolean,  // boolean 
  byte,  // byte 
  Short,  // short 
  Int,  // int 
  Char,  // char 
  Max,
};

struct TreePrimitiveType: public Tree {
  enum NTPrimitiveTypeVariants variant;

  TreePrimitiveType(): Tree(NonTerminalType::PrimitiveType), variant(NTPrimitiveTypeVariants::Max){

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

enum class NTBooleanLiteralVariants {
  Max,
};

struct TreeBooleanLiteral: public Tree {
  enum NTBooleanLiteralVariants variant;
  bool value;

  TreeBooleanLiteral(): Tree(NonTerminalType::BooleanLiteral), variant(NTBooleanLiteralVariants::Max){

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

enum class NTUnaryExpressionNotPlusMinusVariants {
  Primary,  // Primary 
  Name,  // Name 
  BangUnaryExpression,  // ! UnaryExpression 
  CastExpression,  // CastExpression 
  Max,
};

struct TreeUnaryExpressionNotPlusMinus: public Tree {
  enum NTUnaryExpressionNotPlusMinusVariants variant;
  TreeCastExpression* castExpression;
  TreeUnaryExpression* unaryExpression;
  TreePrimary* primary;
  TreeName* name;

  TreeUnaryExpressionNotPlusMinus(): Tree(NonTerminalType::UnaryExpressionNotPlusMinus), variant(NTUnaryExpressionNotPlusMinusVariants::Max), castExpression(nullptr) , unaryExpression(nullptr) , primary(nullptr) , name(nullptr) {

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

enum class NTConstructorDeclarationVariants {
  ModifiersConstructorDeclaratorBlock,  // Modifiers ConstructorDeclarator Block 
  Max,
};

struct TreeConstructorDeclaration: public Tree {
  enum NTConstructorDeclarationVariants variant;
  TreeBlock* block;
  TreeModifiers* modifiers;
  TreeConstructorDeclarator* constructorDeclarator;

  TreeConstructorDeclaration(): Tree(NonTerminalType::ConstructorDeclaration), variant(NTConstructorDeclarationVariants::Max), block(nullptr) , modifiers(nullptr) , constructorDeclarator(nullptr) {

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

enum class NTClassDeclarationVariants {
  ModifiersClassIdentifierClassBody,  // Modifiers class Identifier ClassBody 
  ModifiersClassIdentifierextendsClassTypeClassBody,  // Modifiers class Identifier extends ClassType ClassBody 
  ModifiersClassIdentifierimplementsInterfaceTypeListClassBody,  // Modifiers class Identifier implements InterfaceTypeList ClassBody 
  ModifiersClassIdentifierextendsClassTypeimplementsInterfaceTypeListClassBody,  // Modifiers class Identifier extends ClassType implements InterfaceTypeList ClassBody 
  Max,
};

struct TreeClassDeclaration: public Tree {
  enum NTClassDeclarationVariants variant;
  TreeClassType* classType;
  TreeClassBody* classBody;
  TreeModifiers* modifiers;
  TreeInterfaceTypeList* interfaceTypeList;
  TreeIdentifier* identifier;

  TreeClassDeclaration(): Tree(NonTerminalType::ClassDeclaration), variant(NTClassDeclarationVariants::Max), classType(nullptr) , classBody(nullptr) , modifiers(nullptr) , interfaceTypeList(nullptr) , identifier(nullptr) {

  }
};

enum class NTThis2Variants {
  This2,  // this 
  Max,
};

struct TreeThis2: public Tree {
  enum NTThis2Variants variant;

  TreeThis2(): Tree(NonTerminalType::This2), variant(NTThis2Variants::Max){

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

enum class NTClassMemberDeclarationsVariants {
  ClassMemberDeclaration,  // ClassMemberDeclaration 
  ClassMemberDeclarationsClassMemberDeclaration,  // ClassMemberDeclarations ClassMemberDeclaration 
  Max,
};

struct TreeClassMemberDeclarations: public Tree {
  enum NTClassMemberDeclarationsVariants variant;
  TreeClassMemberDeclarations* classMemberDeclarations;
  TreeClassMemberDeclaration* classMemberDeclaration;

  TreeClassMemberDeclarations(): Tree(NonTerminalType::ClassMemberDeclarations), variant(NTClassMemberDeclarationsVariants::Max), classMemberDeclarations(nullptr) , classMemberDeclaration(nullptr) {

  }
};

enum class NTFormalParameterVariants {
  TypeIdentifier,  // Type Identifier 
  Max,
};

struct TreeFormalParameter: public Tree {
  enum NTFormalParameterVariants variant;
  TreeIdentifier* identifier;
  TreeType* type;

  TreeFormalParameter(): Tree(NonTerminalType::FormalParameter), variant(NTFormalParameterVariants::Max), identifier(nullptr) , type(nullptr) {

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

enum class NTVariableDeclaratorVariants {
  Identifier,  // Identifier 
  IdentifierEqExpression,  // Identifier = Expression 
  Max,
};

struct TreeVariableDeclarator: public Tree {
  enum NTVariableDeclaratorVariants variant;
  TreeExpression* expression;
  TreeIdentifier* identifier;

  TreeVariableDeclarator(): Tree(NonTerminalType::VariableDeclarator), variant(NTVariableDeclaratorVariants::Max), expression(nullptr) , identifier(nullptr) {

  }
};

enum class NTInterfaceMemberDeclarationVariants {
  AbstractMethodDeclaration,  // AbstractMethodDeclaration 
  Max,
};

struct TreeInterfaceMemberDeclaration: public Tree {
  enum NTInterfaceMemberDeclarationVariants variant;
  TreeAbstractMethodDeclaration* abstractMethodDeclaration;

  TreeInterfaceMemberDeclaration(): Tree(NonTerminalType::InterfaceMemberDeclaration), variant(NTInterfaceMemberDeclarationVariants::Max), abstractMethodDeclaration(nullptr) {

  }
};

enum class NTMethodDeclaratorVariants {
  IdentifierLParRPar,  // Identifier ( ) 
  IdentifierLParFormalParameterListRPar,  // Identifier ( FormalParameterList ) 
  Max,
};

struct TreeMethodDeclarator: public Tree {
  enum NTMethodDeclaratorVariants variant;
  TreeFormalParameterList* formalParameterList;
  TreeIdentifier* identifier;

  TreeMethodDeclarator(): Tree(NonTerminalType::MethodDeclarator), variant(NTMethodDeclaratorVariants::Max), formalParameterList(nullptr) , identifier(nullptr) {

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

enum class NTMethodBodyVariants {
  Block,  // Block 
  AbstractMethodBody,  // AbstractMethodBody 
  Max,
};

struct TreeMethodBody: public Tree {
  enum NTMethodBodyVariants variant;
  TreeAbstractMethodBody* abstractMethodBody;
  TreeBlock* block;

  TreeMethodBody(): Tree(NonTerminalType::MethodBody), variant(NTMethodBodyVariants::Max), abstractMethodBody(nullptr) , block(nullptr) {

  }
};

enum class NTFieldDeclarationVariants {
  ModifiersTypeVariableDeclaratorSCol,  // Modifiers Type VariableDeclarator ; 
  Max,
};

struct TreeFieldDeclaration: public Tree {
  enum NTFieldDeclarationVariants variant;
  TreeVariableDeclarator* variableDeclarator;
  TreeModifiers* modifiers;
  TreeType* type;

  TreeFieldDeclaration(): Tree(NonTerminalType::FieldDeclaration), variant(NTFieldDeclarationVariants::Max), variableDeclarator(nullptr) , modifiers(nullptr) , type(nullptr) {

  }
};

enum class NTAbstractMethodBodyVariants {
  SCol,  // ; 
  Max,
};

struct TreeAbstractMethodBody: public Tree {
  enum NTAbstractMethodBodyVariants variant;

  TreeAbstractMethodBody(): Tree(NonTerminalType::AbstractMethodBody), variant(NTAbstractMethodBodyVariants::Max){

  }
};

enum class NTPrimaryNoNewArrayVariants {
  Literal,  // Literal 
  This2,  // This2 
  ParenthesizedExpression,  // ParenthesizedExpression 
  ClassInstanceCreationExpression,  // ClassInstanceCreationExpression 
  FieldAccess,  // FieldAccess 
  MethodInvocation,  // MethodInvocation 
  ArrayAccess,  // ArrayAccess 
  Max,
};

struct TreePrimaryNoNewArray: public Tree {
  enum NTPrimaryNoNewArrayVariants variant;
  TreeMethodInvocation* methodInvocation;
  TreeThis2* this2;
  TreeLiteral* literal;
  TreeArrayAccess* arrayAccess;
  TreeParenthesizedExpression* parenthesizedExpression;
  TreeClassInstanceCreationExpression* classInstanceCreationExpression;
  TreeFieldAccess* fieldAccess;

  TreePrimaryNoNewArray(): Tree(NonTerminalType::PrimaryNoNewArray), variant(NTPrimaryNoNewArrayVariants::Max), methodInvocation(nullptr) , this2(nullptr) , literal(nullptr) , arrayAccess(nullptr) , parenthesizedExpression(nullptr) , classInstanceCreationExpression(nullptr) , fieldAccess(nullptr) {

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

enum class NTConstructorDeclaratorVariants {
  IdentifierLParRPar,  // Identifier ( ) 
  IdentifierLParFormalParameterListRPar,  // Identifier ( FormalParameterList ) 
  Max,
};

struct TreeConstructorDeclarator: public Tree {
  enum NTConstructorDeclaratorVariants variant;
  TreeFormalParameterList* formalParameterList;
  TreeIdentifier* identifier;

  TreeConstructorDeclarator(): Tree(NonTerminalType::ConstructorDeclarator), variant(NTConstructorDeclaratorVariants::Max), formalParameterList(nullptr) , identifier(nullptr) {

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

} // namespace Parse 
#endif // PARSERAST_DISABLED
