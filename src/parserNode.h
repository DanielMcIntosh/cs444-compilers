#pragma once
#ifndef PARSERAST_DISABLED
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
  This2,                    // this 
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
  AssignmentExpression, 
  ConditionalAndExpression, 
  EqualityExpression, 
  MultiplicativeExpression, 
  CastExpression, 
  MethodInvocation, 
  ConditionalOrExpression, 
  FieldAccess, 
  ParenthesizedExpression, 
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
  SingleTypeImportDeclaration, 
  ImportDeclaration, 
  ClassMemberDeclaration, 
  IntegerLiteral, 
  ArrayType, 
  RelationalExpression, 
  ClassType, 
  LocalVariableDeclaration, 
  NullLiteral, 
  ExpressionStatement, 
  ClassOrInterfaceType, 
  ArrayCreationExpression, 
  Name, 
  ClassBody, 
  BooleanLiteral, 
  TypeDeclaration, 
  StatementWithoutTrailingSubstatement, 
  Identifier, 
  InterfaceType, 
  CompilationUnit, 
  ForStatementNoShortIf, 
  CharacterLiteral, 
  ExtendsInterfaces, 
  Goal, 
  StatementExpression, 
  ImportDeclarations, 
  ReferenceType, 
  UnaryExpression, 
  StringLiteral, 
  PrimitiveType, 
  MethodHeader, 
  Modifiers, 
  PackageDeclaration, 
  MethodDeclaration, 
  Literal, 
  UnaryExpressionNotPlusMinus, 
  Type, 
  ConstructorDeclaration, 
  Modifier, 
  ClassInstanceCreationExpression, 
  ClassDeclaration, 
  This2, 
  InterfaceTypeList, 
  ClassMemberDeclarations, 
  FormalParameter, 
  Assignment, 
  TypeImportOnDemandDeclaration, 
  VariableDeclarator, 
  InterfaceMemberDeclaration, 
  MethodDeclarator, 
  FormalParameterList, 
  IfThenElseStatementNoShortIf, 
  MethodBody, 
  FieldDeclaration, 
  AbstractMethodBody, 
  PrimaryNoNewArray, 
  InterfaceBody, 
  ConstructorDeclarator, 
  ArrayAccess, 
  InterfaceDeclaration, 
  WhileStatementNoShortIf, 
  BlockStatement, 
  InterfaceMemberDeclarations, 
  AbstractMethodDeclaration, 
  Max,
};

struct TreeLeftHandSide;
struct TreeAssignmentExpression;
struct TreeConditionalAndExpression;
struct TreeEqualityExpression;
struct TreeMultiplicativeExpression;
struct TreeCastExpression;
struct TreeMethodInvocation;
struct TreeConditionalOrExpression;
struct TreeFieldAccess;
struct TreeParenthesizedExpression;
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
struct TreeSingleTypeImportDeclaration;
struct TreeImportDeclaration;
struct TreeClassMemberDeclaration;
struct TreeIntegerLiteral;
struct TreeArrayType;
struct TreeRelationalExpression;
struct TreeClassType;
struct TreeLocalVariableDeclaration;
struct TreeNullLiteral;
struct TreeExpressionStatement;
struct TreeClassOrInterfaceType;
struct TreeArrayCreationExpression;
struct TreeName;
struct TreeClassBody;
struct TreeBooleanLiteral;
struct TreeTypeDeclaration;
struct TreeStatementWithoutTrailingSubstatement;
struct TreeIdentifier;
struct TreeInterfaceType;
struct TreeCompilationUnit;
struct TreeForStatementNoShortIf;
struct TreeCharacterLiteral;
struct TreeExtendsInterfaces;
struct TreeGoal;
struct TreeStatementExpression;
struct TreeImportDeclarations;
struct TreeReferenceType;
struct TreeUnaryExpression;
struct TreeStringLiteral;
struct TreePrimitiveType;
struct TreeMethodHeader;
struct TreeModifiers;
struct TreePackageDeclaration;
struct TreeMethodDeclaration;
struct TreeLiteral;
struct TreeUnaryExpressionNotPlusMinus;
struct TreeType;
struct TreeConstructorDeclaration;
struct TreeModifier;
struct TreeClassInstanceCreationExpression;
struct TreeClassDeclaration;
struct TreeThis2;
struct TreeInterfaceTypeList;
struct TreeClassMemberDeclarations;
struct TreeFormalParameter;
struct TreeAssignment;
struct TreeTypeImportOnDemandDeclaration;
struct TreeVariableDeclarator;
struct TreeInterfaceMemberDeclaration;
struct TreeMethodDeclarator;
struct TreeFormalParameterList;
struct TreeIfThenElseStatementNoShortIf;
struct TreeMethodBody;
struct TreeFieldDeclaration;
struct TreeAbstractMethodBody;
struct TreePrimaryNoNewArray;
struct TreeInterfaceBody;
struct TreeConstructorDeclarator;
struct TreeArrayAccess;
struct TreeInterfaceDeclaration;
struct TreeWhileStatementNoShortIf;
struct TreeBlockStatement;
struct TreeInterfaceMemberDeclarations;
struct TreeAbstractMethodDeclaration;

} // namespace Parse 
#endif // PARSERAST_DISABLED
