#pragma once
namespace Parse { 
enum class TerminalType {
  Bang,                     // ! 
  BangEq,                   // != 
  Perc,                     // % 
  Amp,                      // & 
  AmpAmp,                   // && 
  LPar,                     // ( 
  RPar,                     // ) 
  Star,                     // * 
  Plus,                     // + 
  Com,                      // , 
  Minus,                    // - 
  Dot,                      // . 
  RSlash,                   // / 
  SCol,                     // ; 
  Le,                       // < 
  LeEq,                     // <= 
  Eq,                       // = 
  EqEq,                     // == 
  Gr,                       // > 
  GrEq,                     // >= 
  BOF,                      // BOF 
  BooleanLiteral,           // BooleanLiteral 
  CharacterLiteral,         // CharacterLiteral 
  Eof,                      // EOF 
  Identifier,               // Identifier 
  IntegerLiteral,           // IntegerLiteral 
  NullLiteral,              // NullLiteral 
  StringLiteral,            // StringLiteral 
  LSBr,                     // [ 
  RSBr,                     // ] 
  abstract,                 // abstract 
  boolean,                  // boolean 
  byte,                     // byte 
  Char,                     // char 
  Class,                    // class 
  Else,                     // else 
  extends,                  // extends 
  final,                    // final 
  For,                      // for 
  If,                       // if 
  implements,               // implements 
  import,                   // import 
  instanceof,               // instanceof 
  Int,                      // int 
  interface,                // interface 
  native,                   // native 
  New,                      // new 
  package,                  // package 
  Protected,                // protected 
  Public,                   // public 
  Return,                   // return 
  Short,                    // short 
  Static,                   // static 
  This2,                    // this 
  Void,                     // void 
  While,                    // while 
  LCBr,                     // { 
  Or,                       // | 
  OrOr,                     // || 
  RCBr,                     // } 
  Max,
};

enum class NonTerminalType {
  AbstractMethodBody, 
  AbstractMethodDeclaration, 
  AdditiveExpression, 
  AndExpression, 
  ArgumentList, 
  ArrayAccess, 
  ArrayCreationExpression, 
  ArrayType, 
  Assignment, 
  AssignmentExpression, 
  Block, 
  BlockStatement, 
  BlockStatements, 
  BooleanLiteral, 
  CastExpression, 
  CharacterLiteral, 
  ClassBody, 
  ClassDeclaration, 
  ClassInstanceCreationExpression, 
  ClassMemberDeclaration, 
  ClassMemberDeclarations, 
  ClassOrInterfaceType, 
  ClassType, 
  CompilationUnit, 
  ConditionalAndExpression, 
  ConditionalOrExpression, 
  ConstructorDeclaration, 
  ConstructorDeclarator, 
  EqualityExpression, 
  Expression, 
  ExpressionStatement, 
  ExtendsInterfaces, 
  FieldAccess, 
  FieldDeclaration, 
  ForInit, 
  ForStatement, 
  ForStatementNoShortIf, 
  ForUpdate, 
  FormalParameter, 
  FormalParameterList, 
  Goal, 
  Identifier, 
  IfThenElseStatement, 
  IfThenElseStatementNoShortIf, 
  IfThenStatement, 
  ImportDeclaration, 
  ImportDeclarations, 
  InclusiveOrExpression, 
  IntegerLiteral, 
  InterfaceBody, 
  InterfaceDeclaration, 
  InterfaceMemberDeclaration, 
  InterfaceMemberDeclarations, 
  InterfaceType, 
  InterfaceTypeList, 
  LeftHandSide, 
  Literal, 
  LocalVariableDeclaration, 
  LocalVariableDeclarationStatement, 
  MethodBody, 
  MethodDeclaration, 
  MethodDeclarator, 
  MethodHeader, 
  MethodInvocation, 
  Modifier, 
  Modifiers, 
  MultiplicativeExpression, 
  Name, 
  NullLiteral, 
  PackageDeclaration, 
  ParenthesizedExpression, 
  Primary, 
  PrimaryNoNewArray, 
  PrimitiveType, 
  ReferenceType, 
  RelationalExpression, 
  ReturnStatement, 
  SingleTypeImportDeclaration, 
  Statement, 
  StatementExpression, 
  StatementNoShortIf, 
  StatementWithoutTrailingSubstatement, 
  StringLiteral, 
  This2, 
  Type, 
  TypeDeclaration, 
  TypeImportOnDemandDeclaration, 
  UnaryExpression, 
  UnaryExpressionNotPlusMinus, 
  VariableDeclarator, 
  WhileStatement, 
  WhileStatementNoShortIf, 
  Max,
};

struct TAbstractMethodBody;
struct TAbstractMethodDeclaration;
struct TAdditiveExpression;
struct TAndExpression;
struct TArgumentList;
struct TArrayAccess;
struct TArrayCreationExpression;
struct TArrayType;
struct TAssignment;
struct TAssignmentExpression;
struct TBlock;
struct TBlockStatement;
struct TBlockStatements;
struct TBooleanLiteral;
struct TCastExpression;
struct TCharacterLiteral;
struct TClassBody;
struct TClassDeclaration;
struct TClassInstanceCreationExpression;
struct TClassMemberDeclaration;
struct TClassMemberDeclarations;
struct TClassOrInterfaceType;
struct TClassType;
struct TCompilationUnit;
struct TConditionalAndExpression;
struct TConditionalOrExpression;
struct TConstructorDeclaration;
struct TConstructorDeclarator;
struct TEqualityExpression;
struct TExpression;
struct TExpressionStatement;
struct TExtendsInterfaces;
struct TFieldAccess;
struct TFieldDeclaration;
struct TForInit;
struct TForStatement;
struct TForStatementNoShortIf;
struct TForUpdate;
struct TFormalParameter;
struct TFormalParameterList;
struct TGoal;
struct TIdentifier;
struct TIfThenElseStatement;
struct TIfThenElseStatementNoShortIf;
struct TIfThenStatement;
struct TImportDeclaration;
struct TImportDeclarations;
struct TInclusiveOrExpression;
struct TIntegerLiteral;
struct TInterfaceBody;
struct TInterfaceDeclaration;
struct TInterfaceMemberDeclaration;
struct TInterfaceMemberDeclarations;
struct TInterfaceType;
struct TInterfaceTypeList;
struct TLeftHandSide;
struct TLiteral;
struct TLocalVariableDeclaration;
struct TLocalVariableDeclarationStatement;
struct TMethodBody;
struct TMethodDeclaration;
struct TMethodDeclarator;
struct TMethodHeader;
struct TMethodInvocation;
struct TModifier;
struct TModifiers;
struct TMultiplicativeExpression;
struct TName;
struct TNullLiteral;
struct TPackageDeclaration;
struct TParenthesizedExpression;
struct TPrimary;
struct TPrimaryNoNewArray;
struct TPrimitiveType;
struct TReferenceType;
struct TRelationalExpression;
struct TReturnStatement;
struct TSingleTypeImportDeclaration;
struct TStatement;
struct TStatementExpression;
struct TStatementNoShortIf;
struct TStatementWithoutTrailingSubstatement;
struct TStringLiteral;
struct TThis2;
struct TType;
struct TTypeDeclaration;
struct TTypeImportOnDemandDeclaration;
struct TUnaryExpression;
struct TUnaryExpressionNotPlusMinus;
struct TVariableDeclarator;
struct TWhileStatement;
struct TWhileStatementNoShortIf;

} // namespace Parse 
