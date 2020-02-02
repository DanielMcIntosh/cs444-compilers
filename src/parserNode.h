#pragma once
namespace Parse { 
enum class TerminalType {
  StringLiteral,            // StringLiteral 
  CharacterLiteral,         // CharacterLiteral 
  Til,                      // ~ 
  LCBr,                     // { 
  IntegerLiteral,           // IntegerLiteral 
  While,                    // while 
  Gr,                       // > 
  BOF,                      // BOF 
  LeEq,                     // <= 
  LSBr,                     // [ 
  Minus,                    // - 
  byte,                     // byte 
  BangEq,                   // != 
  BooleanLiteral,           // BooleanLiteral 
  Void,                     // void 
  Bang,                     // ! 
  Identifier,               // Identifier 
  Perc,                     // % 
  Com,                      // , 
  This,                     // this 
  Eof,                      // EOF 
  RPar,                     // ) 
  RSBr,                     // ] 
  Eq,                       // = 
  Short,                    // short 
  SCol,                     // ; 
  interface,                // interface 
  New,                      // new 
  OrOr,                     // || 
  abstract,                 // abstract 
  Dot,                      // . 
  Star,                     // * 
  EqEq,                     // == 
  GrEq,                     // >= 
  AmpAmp,                   // && 
  Plus,                     // + 
  boolean,                  // boolean 
  Char,                     // char 
  Static,                   // static 
  Class,                    // class 
  NullLiteral,              // NullLiteral 
  Else,                     // else 
  extends,                  // extends 
  Le,                       // < 
  LPar,                     // ( 
  final,                    // final 
  For,                      // for 
  If,                       // if 
  implements,               // implements 
  import,                   // import 
  instanceof,               // instanceof 
  Int,                      // int 
  native,                   // native 
  package,                  // package 
  RSlash,                   // / 
  Protected,                // protected 
  RCBr,                     // } 
  Public,                   // public 
  Return,                   // return 
  Max,
};

enum class NonTerminalType {
  Expression, 
  Assignment, 
  ConditionalOrExpression, 
  EqualityExpression, 
  AdditiveExpression, 
  MultiplicativeExpression, 
  MethodDeclarator, 
  VariableInitializer, 
  FieldDeclaration, 
  Interfaces, 
  ClassBodyDeclarations, 
  ClassDeclaration, 
  ConstantExpression, 
  ClassInstanceCreationExpression, 
  Modifier, 
  ConstructorDeclaration, 
  ClassBodyDeclaration, 
  CastExpression, 
  ClassMemberDeclaration, 
  TypeDeclaration, 
  MethodHeader, 
  Modifiers, 
  SingleTypeImportDeclaration, 
  FormalParameterList, 
  MethodDeclaration, 
  PackageDeclaration, 
  VariableDeclarator, 
  DimExpr, 
  AssignmentExpression, 
  RelationalExpression, 
  ClassBody, 
  Name, 
  ArrayCreationExpression, 
  ClassOrInterfaceType, 
  Type, 
  ClassTypeList, 
  Literal, 
  InterfaceTypeList, 
  BooleanLiteral, 
  PrimitiveType, 
  Identifier, 
  StatementWithoutTrailingSubstatement, 
  Goal, 
  LeftHandSide, 
  CompilationUnit, 
  CharacterLiteral, 
  InterfaceType, 
  ReferenceType, 
  ImportDeclarations, 
  FormalParameter, 
  StatementExpression, 
  ConstructorBody, 
  LocalVariableDeclaration, 
  ClassType, 
  ArrayType, 
  NumericType, 
  ConstructorDeclarator, 
  UnaryExpressionNotPlusMinus, 
  InterfaceBody, 
  PrimaryNoNewArray, 
  SimpleName, 
  IntegralType, 
  MethodBody, 
  TypeImportOnDemandDeclaration, 
  ExpressionStatement, 
  IfThenElseStatementNoShortIf, 
  InterfaceDeclaration, 
  ExtendsInterfaces, 
  DimExprs, 
  QualifiedName, 
  InterfaceMemberDeclarations, 
  BlockStatement, 
  StringLiteral, 
  WhileStatementNoShortIf, 
  InterfaceMemberDeclaration, 
  PostfixExpression, 
  ConstantDeclaration, 
  AbstractMethodDeclaration, 
  Super, 
  ArrayInitializer, 
  ReturnStatement, 
  VariableInitializers, 
  ImportDeclaration, 
  ForStatementNoShortIf, 
  Block, 
  TypeDeclarations, 
  LocalVariableDeclarationStatement, 
  StaticInitializer, 
  IntegerLiteral, 
  Statement, 
  ArrayAccess, 
  StatementNoShortIf, 
  EmptyStatement, 
  ForStatement, 
  IfThenStatement, 
  VariableDeclaratorId, 
  NullLiteral, 
  ArgumentList, 
  IfThenElseStatement, 
  WhileStatement, 
  Primary, 
  ForInit, 
  ConditionalAndExpression, 
  ForUpdate, 
  UnaryExpression, 
  Dims, 
  BlockStatements, 
  FieldAccess, 
  MethodInvocation, 
  Max,
};

struct TreeExpression;
struct TreeAssignment;
struct TreeConditionalOrExpression;
struct TreeEqualityExpression;
struct TreeAdditiveExpression;
struct TreeMultiplicativeExpression;
struct TreeMethodDeclarator;
struct TreeVariableInitializer;
struct TreeFieldDeclaration;
struct TreeInterfaces;
struct TreeClassBodyDeclarations;
struct TreeClassDeclaration;
struct TreeConstantExpression;
struct TreeClassInstanceCreationExpression;
struct TreeModifier;
struct TreeConstructorDeclaration;
struct TreeClassBodyDeclaration;
struct TreeCastExpression;
struct TreeClassMemberDeclaration;
struct TreeTypeDeclaration;
struct TreeMethodHeader;
struct TreeModifiers;
struct TreeSingleTypeImportDeclaration;
struct TreeFormalParameterList;
struct TreeMethodDeclaration;
struct TreePackageDeclaration;
struct TreeVariableDeclarator;
struct TreeDimExpr;
struct TreeAssignmentExpression;
struct TreeRelationalExpression;
struct TreeClassBody;
struct TreeName;
struct TreeArrayCreationExpression;
struct TreeClassOrInterfaceType;
struct TreeType;
struct TreeClassTypeList;
struct TreeLiteral;
struct TreeInterfaceTypeList;
struct TreeBooleanLiteral;
struct TreePrimitiveType;
struct TreeIdentifier;
struct TreeStatementWithoutTrailingSubstatement;
struct TreeGoal;
struct TreeLeftHandSide;
struct TreeCompilationUnit;
struct TreeCharacterLiteral;
struct TreeInterfaceType;
struct TreeReferenceType;
struct TreeImportDeclarations;
struct TreeFormalParameter;
struct TreeStatementExpression;
struct TreeConstructorBody;
struct TreeLocalVariableDeclaration;
struct TreeClassType;
struct TreeArrayType;
struct TreeNumericType;
struct TreeConstructorDeclarator;
struct TreeUnaryExpressionNotPlusMinus;
struct TreeInterfaceBody;
struct TreePrimaryNoNewArray;
struct TreeSimpleName;
struct TreeIntegralType;
struct TreeMethodBody;
struct TreeTypeImportOnDemandDeclaration;
struct TreeExpressionStatement;
struct TreeIfThenElseStatementNoShortIf;
struct TreeInterfaceDeclaration;
struct TreeExtendsInterfaces;
struct TreeDimExprs;
struct TreeQualifiedName;
struct TreeInterfaceMemberDeclarations;
struct TreeBlockStatement;
struct TreeStringLiteral;
struct TreeWhileStatementNoShortIf;
struct TreeInterfaceMemberDeclaration;
struct TreePostfixExpression;
struct TreeConstantDeclaration;
struct TreeAbstractMethodDeclaration;
struct TreeSuper;
struct TreeArrayInitializer;
struct TreeReturnStatement;
struct TreeVariableInitializers;
struct TreeImportDeclaration;
struct TreeForStatementNoShortIf;
struct TreeBlock;
struct TreeTypeDeclarations;
struct TreeLocalVariableDeclarationStatement;
struct TreeStaticInitializer;
struct TreeIntegerLiteral;
struct TreeStatement;
struct TreeArrayAccess;
struct TreeStatementNoShortIf;
struct TreeEmptyStatement;
struct TreeForStatement;
struct TreeIfThenStatement;
struct TreeVariableDeclaratorId;
struct TreeNullLiteral;
struct TreeArgumentList;
struct TreeIfThenElseStatement;
struct TreeWhileStatement;
struct TreePrimary;
struct TreeForInit;
struct TreeConditionalAndExpression;
struct TreeForUpdate;
struct TreeUnaryExpression;
struct TreeDims;
struct TreeBlockStatements;
struct TreeFieldAccess;
struct TreeMethodInvocation;

} // namespace Parse 
