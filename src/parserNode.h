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
  LeftHandSide, 
  ConditionalAndExpression, 
  EqualityExpression, 
  MultiplicativeExpression, 
  CastExpression, 
  MethodInvocation, 
  ConditionalOrExpression, 
  FieldAccess, 
  Dims, 
  AdditiveExpression, 
  ReturnStatement, 
  ForUpdate, 
  ForInit, 
  Primary, 
  WhileStatement, 
  IfThenElseStatement, 
  ArgumentList, 
  IfThenStatement, 
  ForStatement, 
  EmptyStatement, 
  StatementNoShortIf, 
  Statement, 
  Expression, 
  LocalVariableDeclarationStatement, 
  BlockStatements, 
  Block, 
  AbstractMethodDeclaration, 
  InterfaceMemberDeclaration, 
  WhileStatementNoShortIf, 
  BlockStatement, 
  InterfaceMemberDeclarations, 
  ImportDeclaration, 
  ClassMemberDeclaration, 
  AssignmentExpression, 
  TypeDeclarations, 
  SimpleName, 
  IntegerLiteral, 
  ArrayType, 
  RelationalExpression, 
  ClassType, 
  LocalVariableDeclaration, 
  NullLiteral, 
  ExpressionStatement, 
  ClassOrInterfaceType, 
  DimExprs, 
  ArrayCreationExpression, 
  Name, 
  ClassBody, 
  ForStatementNoShortIf, 
  CharacterLiteral, 
  ExtendsInterfaces, 
  InterfaceType, 
  CompilationUnit, 
  Goal, 
  StatementExpression, 
  ImportDeclarations, 
  ReferenceType, 
  StatementWithoutTrailingSubstatement, 
  Identifier, 
  UnaryExpression, 
  StringLiteral, 
  PrimitiveType, 
  MethodHeader, 
  Modifiers, 
  BooleanLiteral, 
  DimExpr, 
  PackageDeclaration, 
  MethodDeclaration, 
  Literal, 
  UnaryExpressionNotPlusMinus, 
  ClassTypeList, 
  Type, 
  TypeDeclaration, 
  FieldDeclaration, 
  ConstructorDeclaration, 
  Modifier, 
  ClassInstanceCreationExpression, 
  ClassDeclaration, 
  InterfaceTypeList, 
  ClassMemberDeclarations, 
  FormalParameter, 
  Assignment, 
  TypeImportOnDemandDeclaration, 
  VariableDeclarator, 
  MethodDeclarator, 
  FormalParameterList, 
  IfThenElseStatementNoShortIf, 
  MethodBody, 
  PrimaryNoNewArray, 
  InterfaceBody, 
  ConstructorDeclarator, 
  ArrayAccess, 
  InterfaceDeclaration, 
  SingleTypeImportDeclaration, 
  ConstructorBody, 
  Max,
};

struct TreeLeftHandSide;
struct TreeConditionalAndExpression;
struct TreeEqualityExpression;
struct TreeMultiplicativeExpression;
struct TreeCastExpression;
struct TreeMethodInvocation;
struct TreeConditionalOrExpression;
struct TreeFieldAccess;
struct TreeDims;
struct TreeAdditiveExpression;
struct TreeReturnStatement;
struct TreeForUpdate;
struct TreeForInit;
struct TreePrimary;
struct TreeWhileStatement;
struct TreeIfThenElseStatement;
struct TreeArgumentList;
struct TreeIfThenStatement;
struct TreeForStatement;
struct TreeEmptyStatement;
struct TreeStatementNoShortIf;
struct TreeStatement;
struct TreeExpression;
struct TreeLocalVariableDeclarationStatement;
struct TreeBlockStatements;
struct TreeBlock;
struct TreeAbstractMethodDeclaration;
struct TreeInterfaceMemberDeclaration;
struct TreeWhileStatementNoShortIf;
struct TreeBlockStatement;
struct TreeInterfaceMemberDeclarations;
struct TreeImportDeclaration;
struct TreeClassMemberDeclaration;
struct TreeAssignmentExpression;
struct TreeTypeDeclarations;
struct TreeSimpleName;
struct TreeIntegerLiteral;
struct TreeArrayType;
struct TreeRelationalExpression;
struct TreeClassType;
struct TreeLocalVariableDeclaration;
struct TreeNullLiteral;
struct TreeExpressionStatement;
struct TreeClassOrInterfaceType;
struct TreeDimExprs;
struct TreeArrayCreationExpression;
struct TreeName;
struct TreeClassBody;
struct TreeForStatementNoShortIf;
struct TreeCharacterLiteral;
struct TreeExtendsInterfaces;
struct TreeInterfaceType;
struct TreeCompilationUnit;
struct TreeGoal;
struct TreeStatementExpression;
struct TreeImportDeclarations;
struct TreeReferenceType;
struct TreeStatementWithoutTrailingSubstatement;
struct TreeIdentifier;
struct TreeUnaryExpression;
struct TreeStringLiteral;
struct TreePrimitiveType;
struct TreeMethodHeader;
struct TreeModifiers;
struct TreeBooleanLiteral;
struct TreeDimExpr;
struct TreePackageDeclaration;
struct TreeMethodDeclaration;
struct TreeLiteral;
struct TreeUnaryExpressionNotPlusMinus;
struct TreeClassTypeList;
struct TreeType;
struct TreeTypeDeclaration;
struct TreeFieldDeclaration;
struct TreeConstructorDeclaration;
struct TreeModifier;
struct TreeClassInstanceCreationExpression;
struct TreeClassDeclaration;
struct TreeInterfaceTypeList;
struct TreeClassMemberDeclarations;
struct TreeFormalParameter;
struct TreeAssignment;
struct TreeTypeImportOnDemandDeclaration;
struct TreeVariableDeclarator;
struct TreeMethodDeclarator;
struct TreeFormalParameterList;
struct TreeIfThenElseStatementNoShortIf;
struct TreeMethodBody;
struct TreePrimaryNoNewArray;
struct TreeInterfaceBody;
struct TreeConstructorDeclarator;
struct TreeArrayAccess;
struct TreeInterfaceDeclaration;
struct TreeSingleTypeImportDeclaration;
struct TreeConstructorBody;

} // namespace Parse 
