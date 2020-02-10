#pragma once
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
  ForStatement, 
  Primary, 
  WhileStatement, 
  IfThenElseStatement, 
  ArgumentList, 
  IfThenStatement, 
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

struct TLeftHandSide;
struct TAssignmentExpression;
struct TConditionalAndExpression;
struct TAndExpression;
struct TEqualityExpression;
struct TMultiplicativeExpression;
struct TCastExpression;
struct TMethodInvocation;
struct TConditionalOrExpression;
struct TFieldAccess;
struct TParenthesizedExpression;
struct TAdditiveExpression;
struct TReturnStatement;
struct TForUpdate;
struct TForInit;
struct TForStatement;
struct TPrimary;
struct TWhileStatement;
struct TIfThenElseStatement;
struct TArgumentList;
struct TIfThenStatement;
struct TStatementNoShortIf;
struct TStatement;
struct TExpression;
struct TLocalVariableDeclarationStatement;
struct TBlockStatements;
struct TBlock;
struct TSingleTypeImportDeclaration;
struct TImportDeclaration;
struct TClassMemberDeclaration;
struct TIntegerLiteral;
struct TArrayType;
struct TRelationalExpression;
struct TClassType;
struct TLocalVariableDeclaration;
struct TNullLiteral;
struct TExpressionStatement;
struct TClassOrInterfaceType;
struct TArrayCreationExpression;
struct TName;
struct TClassBody;
struct TInterfaceType;
struct TCompilationUnit;
struct TForStatementNoShortIf;
struct TCharacterLiteral;
struct TExtendsInterfaces;
struct TGoal;
struct TStatementExpression;
struct TImportDeclarations;
struct TReferenceType;
struct TTypeDeclaration;
struct TInclusiveOrExpression;
struct TStatementWithoutTrailingSubstatement;
struct TIdentifier;
struct TUnaryExpression;
struct TStringLiteral;
struct TPrimitiveType;
struct TMethodHeader;
struct TModifiers;
struct TBooleanLiteral;
struct TPackageDeclaration;
struct TMethodDeclaration;
struct TLiteral;
struct TUnaryExpressionNotPlusMinus;
struct TType;
struct TConstructorDeclaration;
struct TModifier;
struct TClassInstanceCreationExpression;
struct TClassDeclaration;
struct TThis2;
struct TInterfaceTypeList;
struct TClassMemberDeclarations;
struct TFormalParameter;
struct TAssignment;
struct TTypeImportOnDemandDeclaration;
struct TVariableDeclarator;
struct TInterfaceMemberDeclaration;
struct TMethodDeclarator;
struct TFormalParameterList;
struct TIfThenElseStatementNoShortIf;
struct TMethodBody;
struct TFieldDeclaration;
struct TAbstractMethodBody;
struct TPrimaryNoNewArray;
struct TInterfaceBody;
struct TConstructorDeclarator;
struct TArrayAccess;
struct TInterfaceDeclaration;
struct TWhileStatementNoShortIf;
struct TBlockStatement;
struct TInterfaceMemberDeclarations;
struct TAbstractMethodDeclaration;

} // namespace Parse 
