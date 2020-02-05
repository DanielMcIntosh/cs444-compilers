#pragma once
#ifndef PARSERAST_DISABLED
namespace Parse { 
enum class TerminalType {
  StringLiteral,            // StringLiteral 
  CharacterLiteral,         // CharacterLiteral 
  Or,                       // | 
  LCBr,                     // { 
  IntegerLiteral,           // IntegerLiteral 
  While,                    // while 
  This2,                    // this 
  LSBr,                     // [ 
  Minus,                    // - 
  byte,                     // byte 
  Eq,                       // = 
  Short,                    // short 
  SCol,                     // ; 
  interface,                // interface 
  New,                      // new 
  RPar,                     // ) 
  RSBr,                     // ] 
  BangEq,                   // != 
  Amp,                      // & 
  BooleanLiteral,           // BooleanLiteral 
  Void,                     // void 
  Bang,                     // ! 
  BOF,                      // BOF 
  Gr,                       // > 
  OrOr,                     // || 
  abstract,                 // abstract 
  Star,                     // * 
  Dot,                      // . 
  Eof,                      // EOF 
  Identifier,               // Identifier 
  Perc,                     // % 
  Com,                      // , 
  EqEq,                     // == 
  Plus,                     // + 
  GrEq,                     // >= 
  AmpAmp,                   // && 
  LeEq,                     // <= 
  boolean,                  // boolean 
  Char,                     // char 
  Static,                   // static 
  Class,                    // class 
  NullLiteral,              // NullLiteral 
  Else,                     // else 
  extends,                  // extends 
  LPar,                     // ( 
  Le,                       // < 
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
  AndExpression, 
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
  InterfaceType, 
  CompilationUnit, 
  ForStatementNoShortIf, 
  CharacterLiteral, 
  ExtendsInterfaces, 
  Goal, 
  StatementExpression, 
  ImportDeclarations, 
  ReferenceType, 
  TypeDeclaration, 
  InclusiveOrExpression, 
  StatementWithoutTrailingSubstatement, 
  Identifier, 
  UnaryExpression, 
  StringLiteral, 
  PrimitiveType, 
  MethodHeader, 
  Modifiers, 
  BooleanLiteral, 
  PackageDeclaration, 
  MethodDeclaration, 
  Literal, 
  ExclusiveOrExpression, 
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
struct TreeAndExpression;
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
struct TreeInterfaceType;
struct TreeCompilationUnit;
struct TreeForStatementNoShortIf;
struct TreeCharacterLiteral;
struct TreeExtendsInterfaces;
struct TreeGoal;
struct TreeStatementExpression;
struct TreeImportDeclarations;
struct TreeReferenceType;
struct TreeTypeDeclaration;
struct TreeInclusiveOrExpression;
struct TreeStatementWithoutTrailingSubstatement;
struct TreeIdentifier;
struct TreeUnaryExpression;
struct TreeStringLiteral;
struct TreePrimitiveType;
struct TreeMethodHeader;
struct TreeModifiers;
struct TreeBooleanLiteral;
struct TreePackageDeclaration;
struct TreeMethodDeclaration;
struct TreeLiteral;
struct TreeExclusiveOrExpression;
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
