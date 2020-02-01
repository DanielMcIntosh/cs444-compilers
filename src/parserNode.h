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
  SingleTypeImportDeclaration, 
  ConstructorDeclarator, 
  NumericType, 
  PrimaryNoNewArray, 
  MethodDeclarator, 
  VariableInitializer, 
  FieldDeclaration, 
  Interfaces, 
  ClassBodyDeclarations, 
  InterfaceTypeList, 
  ClassDeclaration, 
  ConstantExpression, 
  ClassInstanceCreationExpression, 
  Modifier, 
  ConstructorDeclaration, 
  ClassTypeList, 
  Type, 
  InterfaceBody, 
  UnaryExpressionNotPlusMinus, 
  ArrayType, 
  ClassType, 
  AssignmentExpression, 
  RelationalExpression, 
  ClassBody, 
  Name, 
  ArrayCreationExpression, 
  ClassOrInterfaceType, 
  TypeImportOnDemandDeclaration, 
  IfThenElseStatementNoShortIf, 
  ExpressionStatement, 
  InterfaceType, 
  LeftHandSide, 
  CompilationUnit, 
  ReferenceType, 
  ImportDeclarations, 
  FormalParameter, 
  StatementExpression, 
  FormalParameterList, 
  MethodDeclaration, 
  Literal, 
  PackageDeclaration, 
  VariableDeclarator, 
  DimExpr, 
  Goal, 
  SimpleName, 
  ClassBodyDeclaration, 
  MethodHeader, 
  Modifiers, 
  MethodBody, 
  IntegralType, 
  TypeDeclaration, 
  PrimitiveType, 
  InterfaceDeclaration, 
  ExtendsInterfaces, 
  DimExprs, 
  QualifiedName, 
  InterfaceMemberDeclarations, 
  BlockStatement, 
  WhileStatementNoShortIf, 
  InterfaceMemberDeclaration, 
  PostfixExpression, 
  ConstantDeclaration, 
  AbstractMethodDeclaration, 
  Super, 
  ArrayInitializer, 
  ReturnStatement, 
  AdditiveExpression, 
  VariableInitializers, 
  TypeDeclarations, 
  LocalVariableDeclarationStatement, 
  ConstructorBody, 
  LocalVariableDeclaration, 
  StaticInitializer, 
  Statement, 
  ArrayAccess, 
  StatementNoShortIf, 
  StatementWithoutTrailingSubstatement, 
  EmptyStatement, 
  ForStatement, 
  IfThenStatement, 
  VariableDeclaratorId, 
  ArgumentList, 
  IfThenElseStatement, 
  WhileStatement, 
  Primary, 
  ImportDeclaration, 
  Block, 
  ForStatementNoShortIf, 
  ForInit, 
  UnaryExpression, 
  Dims, 
  BlockStatements, 
  FieldAccess, 
  MethodInvocation, 
  ClassMemberDeclaration, 
  CastExpression, 
  MultiplicativeExpression, 
  EqualityExpression, 
  ForUpdate, 
  ConditionalAndExpression, 
  Max,
};

struct TreeStringLiteral;
struct TreeCharacterLiteral;
struct TreeIntegerLiteral;
struct TreeBooleanLiteral;
struct TreeIdentifier;
struct TreeNullLiteral;
struct TreeExpression;
struct TreeAssignment;
struct TreeConditionalOrExpression;
struct TreeSingleTypeImportDeclaration;
struct TreeConstructorDeclarator;
struct TreeNumericType;
struct TreePrimaryNoNewArray;
struct TreeMethodDeclarator;
struct TreeVariableInitializer;
struct TreeFieldDeclaration;
struct TreeInterfaces;
struct TreeClassBodyDeclarations;
struct TreeInterfaceTypeList;
struct TreeClassDeclaration;
struct TreeConstantExpression;
struct TreeClassInstanceCreationExpression;
struct TreeModifier;
struct TreeConstructorDeclaration;
struct TreeClassTypeList;
struct TreeType;
struct TreeInterfaceBody;
struct TreeUnaryExpressionNotPlusMinus;
struct TreeArrayType;
struct TreeClassType;
struct TreeAssignmentExpression;
struct TreeRelationalExpression;
struct TreeClassBody;
struct TreeName;
struct TreeArrayCreationExpression;
struct TreeClassOrInterfaceType;
struct TreeTypeImportOnDemandDeclaration;
struct TreeIfThenElseStatementNoShortIf;
struct TreeExpressionStatement;
struct TreeInterfaceType;
struct TreeLeftHandSide;
struct TreeCompilationUnit;
struct TreeReferenceType;
struct TreeImportDeclarations;
struct TreeFormalParameter;
struct TreeStatementExpression;
struct TreeFormalParameterList;
struct TreeMethodDeclaration;
struct TreeLiteral;
struct TreePackageDeclaration;
struct TreeVariableDeclarator;
struct TreeDimExpr;
struct TreeGoal;
struct TreeSimpleName;
struct TreeClassBodyDeclaration;
struct TreeMethodHeader;
struct TreeModifiers;
struct TreeMethodBody;
struct TreeIntegralType;
struct TreeTypeDeclaration;
struct TreePrimitiveType;
struct TreeInterfaceDeclaration;
struct TreeExtendsInterfaces;
struct TreeDimExprs;
struct TreeQualifiedName;
struct TreeInterfaceMemberDeclarations;
struct TreeBlockStatement;
struct TreeWhileStatementNoShortIf;
struct TreeInterfaceMemberDeclaration;
struct TreePostfixExpression;
struct TreeConstantDeclaration;
struct TreeAbstractMethodDeclaration;
struct TreeSuper;
struct TreeArrayInitializer;
struct TreeReturnStatement;
struct TreeAdditiveExpression;
struct TreeVariableInitializers;
struct TreeTypeDeclarations;
struct TreeLocalVariableDeclarationStatement;
struct TreeConstructorBody;
struct TreeLocalVariableDeclaration;
struct TreeStaticInitializer;
struct TreeStatement;
struct TreeArrayAccess;
struct TreeStatementNoShortIf;
struct TreeStatementWithoutTrailingSubstatement;
struct TreeEmptyStatement;
struct TreeForStatement;
struct TreeIfThenStatement;
struct TreeVariableDeclaratorId;
struct TreeArgumentList;
struct TreeIfThenElseStatement;
struct TreeWhileStatement;
struct TreePrimary;
struct TreeImportDeclaration;
struct TreeBlock;
struct TreeForStatementNoShortIf;
struct TreeForInit;
struct TreeUnaryExpression;
struct TreeDims;
struct TreeBlockStatements;
struct TreeFieldAccess;
struct TreeMethodInvocation;
struct TreeClassMemberDeclaration;
struct TreeCastExpression;
struct TreeMultiplicativeExpression;
struct TreeEqualityExpression;
struct TreeForUpdate;
struct TreeConditionalAndExpression;

} // namespace Parse 
