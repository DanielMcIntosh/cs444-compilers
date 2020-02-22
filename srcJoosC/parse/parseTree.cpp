#include "parseTree.h"
namespace Parse { 
TAbstractMethodBody::TAbstractMethodBody(): Tree(NonTerminalType::AbstractMethodBody), v(TAbstractMethodBodyV::Max) {}

TAbstractMethodDeclaration::TAbstractMethodDeclaration(): Tree(NonTerminalType::AbstractMethodDeclaration), v(TAbstractMethodDeclarationV::Max), methodHeader(nullptr) {}

TAdditiveExpression::TAdditiveExpression(): Tree(NonTerminalType::AdditiveExpression), v(TAdditiveExpressionV::Max), additiveExpression(nullptr), multiplicativeExpression(nullptr) {}

TAndExpression::TAndExpression(): Tree(NonTerminalType::AndExpression), v(TAndExpressionV::Max), andExpression(nullptr), equalityExpression(nullptr) {}

TArgumentList::TArgumentList(): Tree(NonTerminalType::ArgumentList), v(TArgumentListV::Max), argumentList(nullptr), expression(nullptr) {}

TArrayAccess::TArrayAccess(): Tree(NonTerminalType::ArrayAccess), v(TArrayAccessV::Max), primaryNoNewArray(nullptr), expression(nullptr), name(nullptr) {}

TArrayCreationExpression::TArrayCreationExpression(): Tree(NonTerminalType::ArrayCreationExpression), v(TArrayCreationExpressionV::Max), classOrInterfaceType(nullptr), expression(nullptr), primitiveType(nullptr) {}

TArrayType::TArrayType(): Tree(NonTerminalType::ArrayType), v(TArrayTypeV::Max), name(nullptr), primitiveType(nullptr) {}

TAssignment::TAssignment(): Tree(NonTerminalType::Assignment), v(TAssignmentV::Max), leftHandSide(nullptr), assignmentExpression(nullptr) {}

TAssignmentExpression::TAssignmentExpression(): Tree(NonTerminalType::AssignmentExpression), v(TAssignmentExpressionV::Max), assignment(nullptr), conditionalOrExpression(nullptr) {}

TBlock::TBlock(): Tree(NonTerminalType::Block), v(TBlockV::Max), blockStatements(nullptr) {}

TBlockStatement::TBlockStatement(): Tree(NonTerminalType::BlockStatement), v(TBlockStatementV::Max), statement(nullptr), localVariableDeclarationStatement(nullptr) {}

TBlockStatements::TBlockStatements(): Tree(NonTerminalType::BlockStatements), v(TBlockStatementsV::Max), blockStatements(nullptr), blockStatement(nullptr) {}

TBooleanLiteral::TBooleanLiteral(): Tree(NonTerminalType::BooleanLiteral), v(TBooleanLiteralV::Max) {}

TCastExpression::TCastExpression(): Tree(NonTerminalType::CastExpression), v(TCastExpressionV::Max), name(nullptr), expression(nullptr), unaryExpression(nullptr), unaryExpressionNotPlusMinus(nullptr), primitiveType(nullptr) {}

TCharacterLiteral::TCharacterLiteral(): Tree(NonTerminalType::CharacterLiteral), v(TCharacterLiteralV::Max) {}

TClassBody::TClassBody(): Tree(NonTerminalType::ClassBody), v(TClassBodyV::Max), classMemberDeclarations(nullptr) {}

TClassDeclaration::TClassDeclaration(): Tree(NonTerminalType::ClassDeclaration), v(TClassDeclarationV::Max), classType(nullptr), interfaceTypeList(nullptr), identifier(nullptr), classBody(nullptr), modifiers(nullptr) {}

TClassInstanceCreationExpression::TClassInstanceCreationExpression(): Tree(NonTerminalType::ClassInstanceCreationExpression), v(TClassInstanceCreationExpressionV::Max), argumentList(nullptr), classType(nullptr) {}

TClassMemberDeclaration::TClassMemberDeclaration(): Tree(NonTerminalType::ClassMemberDeclaration), v(TClassMemberDeclarationV::Max), constructorDeclaration(nullptr), fieldDeclaration(nullptr), methodDeclaration(nullptr) {}

TClassMemberDeclarations::TClassMemberDeclarations(): Tree(NonTerminalType::ClassMemberDeclarations), v(TClassMemberDeclarationsV::Max), classMemberDeclarations(nullptr), classMemberDeclaration(nullptr) {}

TClassOrInterfaceType::TClassOrInterfaceType(): Tree(NonTerminalType::ClassOrInterfaceType), v(TClassOrInterfaceTypeV::Max), name(nullptr) {}

TClassType::TClassType(): Tree(NonTerminalType::ClassType), v(TClassTypeV::Max), classOrInterfaceType(nullptr) {}

TCompilationUnit::TCompilationUnit(): Tree(NonTerminalType::CompilationUnit), v(TCompilationUnitV::Max), typeDeclaration(nullptr), packageDeclaration(nullptr), importDeclarations(nullptr) {}

TConditionalAndExpression::TConditionalAndExpression(): Tree(NonTerminalType::ConditionalAndExpression), v(TConditionalAndExpressionV::Max), conditionalAndExpression(nullptr), inclusiveOrExpression(nullptr) {}

TConditionalOrExpression::TConditionalOrExpression(): Tree(NonTerminalType::ConditionalOrExpression), v(TConditionalOrExpressionV::Max), conditionalOrExpression(nullptr), conditionalAndExpression(nullptr) {}

TConstructorDeclaration::TConstructorDeclaration(): Tree(NonTerminalType::ConstructorDeclaration), v(TConstructorDeclarationV::Max), constructorDeclarator(nullptr), block(nullptr), modifiers(nullptr) {}

TConstructorDeclarator::TConstructorDeclarator(): Tree(NonTerminalType::ConstructorDeclarator), v(TConstructorDeclaratorV::Max), formalParameterList(nullptr), identifier(nullptr) {}

TEqualityExpression::TEqualityExpression(): Tree(NonTerminalType::EqualityExpression), v(TEqualityExpressionV::Max), equalityExpression(nullptr), relationalExpression(nullptr) {}

TExpression::TExpression(): Tree(NonTerminalType::Expression), v(TExpressionV::Max), assignmentExpression(nullptr) {}

TExpressionStatement::TExpressionStatement(): Tree(NonTerminalType::ExpressionStatement), v(TExpressionStatementV::Max), statementExpression(nullptr) {}

TExtendsInterfaces::TExtendsInterfaces(): Tree(NonTerminalType::ExtendsInterfaces), v(TExtendsInterfacesV::Max), extendsInterfaces(nullptr), interfaceType(nullptr) {}

TFieldAccess::TFieldAccess(): Tree(NonTerminalType::FieldAccess), v(TFieldAccessV::Max), primary(nullptr), identifier(nullptr) {}

TFieldDeclaration::TFieldDeclaration(): Tree(NonTerminalType::FieldDeclaration), v(TFieldDeclarationV::Max), modifiers(nullptr), variableDeclaration(nullptr) {}

TForInit::TForInit(): Tree(NonTerminalType::ForInit), v(TForInitV::Max), localVariableDeclarationStatement(nullptr), expressionStatement(nullptr) {}

TForStatement::TForStatement(): Tree(NonTerminalType::ForStatement), v(TForStatementV::Max), forUpdate(nullptr), expression(nullptr), statement(nullptr), forInit(nullptr) {}

TForStatementNoShortIf::TForStatementNoShortIf(): Tree(NonTerminalType::ForStatementNoShortIf), v(TForStatementNoShortIfV::Max), forUpdate(nullptr), expression(nullptr), statementNoShortIf(nullptr), forInit(nullptr) {}

TForUpdate::TForUpdate(): Tree(NonTerminalType::ForUpdate), v(TForUpdateV::Max), statementExpression(nullptr) {}

TFormalParameter::TFormalParameter(): Tree(NonTerminalType::FormalParameter), v(TFormalParameterV::Max), type(nullptr), identifier(nullptr) {}

TFormalParameterList::TFormalParameterList(): Tree(NonTerminalType::FormalParameterList), v(TFormalParameterListV::Max), formalParameterList(nullptr), formalParameter(nullptr) {}

TGoal::TGoal(): Tree(NonTerminalType::Goal), v(TGoalV::Max), compilationUnit(nullptr) {}

TIdentifier::TIdentifier(): Tree(NonTerminalType::Identifier), v(TIdentifierV::Max) {}

TIfThenElseStatement::TIfThenElseStatement(): Tree(NonTerminalType::IfThenElseStatement), v(TIfThenElseStatementV::Max), statementNoShortIf(nullptr), statement(nullptr), expression(nullptr) {}

TIfThenElseStatementNoShortIf::TIfThenElseStatementNoShortIf(): Tree(NonTerminalType::IfThenElseStatementNoShortIf), v(TIfThenElseStatementNoShortIfV::Max), expression(nullptr), statementNoShortIf(nullptr), statementNoShortIf2(nullptr) {}

TIfThenStatement::TIfThenStatement(): Tree(NonTerminalType::IfThenStatement), v(TIfThenStatementV::Max), expression(nullptr), statement(nullptr) {}

TImportDeclaration::TImportDeclaration(): Tree(NonTerminalType::ImportDeclaration), v(TImportDeclarationV::Max), typeImportOnDemandDeclaration(nullptr), singleTypeImportDeclaration(nullptr) {}

TImportDeclarations::TImportDeclarations(): Tree(NonTerminalType::ImportDeclarations), v(TImportDeclarationsV::Max), importDeclarations(nullptr), importDeclaration(nullptr) {}

TInclusiveOrExpression::TInclusiveOrExpression(): Tree(NonTerminalType::InclusiveOrExpression), v(TInclusiveOrExpressionV::Max), inclusiveOrExpression(nullptr), andExpression(nullptr) {}

TIntegerLiteral::TIntegerLiteral(): Tree(NonTerminalType::IntegerLiteral), v(TIntegerLiteralV::Max) {}

TInterfaceBody::TInterfaceBody(): Tree(NonTerminalType::InterfaceBody), v(TInterfaceBodyV::Max), interfaceMemberDeclarations(nullptr) {}

TInterfaceDeclaration::TInterfaceDeclaration(): Tree(NonTerminalType::InterfaceDeclaration), v(TInterfaceDeclarationV::Max), extendsInterfaces(nullptr), modifiers(nullptr), interfaceBody(nullptr), identifier(nullptr) {}

TInterfaceMemberDeclaration::TInterfaceMemberDeclaration(): Tree(NonTerminalType::InterfaceMemberDeclaration), v(TInterfaceMemberDeclarationV::Max), abstractMethodDeclaration(nullptr) {}

TInterfaceMemberDeclarations::TInterfaceMemberDeclarations(): Tree(NonTerminalType::InterfaceMemberDeclarations), v(TInterfaceMemberDeclarationsV::Max), interfaceMemberDeclarations(nullptr), interfaceMemberDeclaration(nullptr) {}

TInterfaceType::TInterfaceType(): Tree(NonTerminalType::InterfaceType), v(TInterfaceTypeV::Max), classOrInterfaceType(nullptr) {}

TInterfaceTypeList::TInterfaceTypeList(): Tree(NonTerminalType::InterfaceTypeList), v(TInterfaceTypeListV::Max), interfaceTypeList(nullptr), interfaceType(nullptr) {}

TLeftHandSide::TLeftHandSide(): Tree(NonTerminalType::LeftHandSide), v(TLeftHandSideV::Max), name(nullptr), arrayAccess(nullptr), fieldAccess(nullptr) {}

TLiteral::TLiteral(): Tree(NonTerminalType::Literal), v(TLiteralV::Max), nullLiteral(nullptr), characterLiteral(nullptr), integerLiteral(nullptr), stringLiteral(nullptr), booleanLiteral(nullptr) {}

TLocalVariableDeclarationStatement::TLocalVariableDeclarationStatement(): Tree(NonTerminalType::LocalVariableDeclarationStatement), v(TLocalVariableDeclarationStatementV::Max), variableDeclaration(nullptr) {}

TMethodBody::TMethodBody(): Tree(NonTerminalType::MethodBody), v(TMethodBodyV::Max), abstractMethodBody(nullptr), block(nullptr) {}

TMethodDeclaration::TMethodDeclaration(): Tree(NonTerminalType::MethodDeclaration), v(TMethodDeclarationV::Max), methodHeader(nullptr), methodBody(nullptr) {}

TMethodDeclarator::TMethodDeclarator(): Tree(NonTerminalType::MethodDeclarator), v(TMethodDeclaratorV::Max), formalParameterList(nullptr), identifier(nullptr) {}

TMethodHeader::TMethodHeader(): Tree(NonTerminalType::MethodHeader), v(TMethodHeaderV::Max), modifiers(nullptr), methodDeclarator(nullptr), type(nullptr) {}

TMethodInvocation::TMethodInvocation(): Tree(NonTerminalType::MethodInvocation), v(TMethodInvocationV::Max), identifier(nullptr), primary(nullptr), name(nullptr), argumentList(nullptr) {}

TModifier::TModifier(): Tree(NonTerminalType::Modifier), v(TModifierV::Max) {}

TModifiers::TModifiers(): Tree(NonTerminalType::Modifiers), v(TModifiersV::Max), modifiers(nullptr), modifier(nullptr) {}

TMultiplicativeExpression::TMultiplicativeExpression(): Tree(NonTerminalType::MultiplicativeExpression), v(TMultiplicativeExpressionV::Max), multiplicativeExpression(nullptr), unaryExpression(nullptr) {}

TName::TName(): Tree(NonTerminalType::Name), v(TNameV::Max), name(nullptr), identifier(nullptr) {}

TNullLiteral::TNullLiteral(): Tree(NonTerminalType::NullLiteral), v(TNullLiteralV::Max) {}

TPackageDeclaration::TPackageDeclaration(): Tree(NonTerminalType::PackageDeclaration), v(TPackageDeclarationV::Max), name(nullptr) {}

TParenthesizedExpression::TParenthesizedExpression(): Tree(NonTerminalType::ParenthesizedExpression), v(TParenthesizedExpressionV::Max), expression(nullptr) {}

TPrimary::TPrimary(): Tree(NonTerminalType::Primary), v(TPrimaryV::Max), arrayCreationExpression(nullptr), primaryNoNewArray(nullptr) {}

TPrimaryNoNewArray::TPrimaryNoNewArray(): Tree(NonTerminalType::PrimaryNoNewArray), v(TPrimaryNoNewArrayV::Max), methodInvocation(nullptr), this2(nullptr), literal(nullptr), arrayAccess(nullptr), parenthesizedExpression(nullptr), classInstanceCreationExpression(nullptr), fieldAccess(nullptr) {}

TPrimitiveType::TPrimitiveType(): Tree(NonTerminalType::PrimitiveType), v(TPrimitiveTypeV::Max) {}

TReferenceType::TReferenceType(): Tree(NonTerminalType::ReferenceType), v(TReferenceTypeV::Max), arrayType(nullptr), classOrInterfaceType(nullptr) {}

TRelationalExpression::TRelationalExpression(): Tree(NonTerminalType::RelationalExpression), v(TRelationalExpressionV::Max), referenceType(nullptr), additiveExpression(nullptr), relationalExpression(nullptr) {}

TReturnStatement::TReturnStatement(): Tree(NonTerminalType::ReturnStatement), v(TReturnStatementV::Max), expression(nullptr) {}

TSingleTypeImportDeclaration::TSingleTypeImportDeclaration(): Tree(NonTerminalType::SingleTypeImportDeclaration), v(TSingleTypeImportDeclarationV::Max), name(nullptr) {}

TStatement::TStatement(): Tree(NonTerminalType::Statement), v(TStatementV::Max), forStatement(nullptr), ifThenElseStatement(nullptr), whileStatement(nullptr), statementWithoutTrailingSubstatement(nullptr), ifThenStatement(nullptr) {}

TStatementExpression::TStatementExpression(): Tree(NonTerminalType::StatementExpression), v(TStatementExpressionV::Max), classInstanceCreationExpression(nullptr), assignment(nullptr), methodInvocation(nullptr) {}

TStatementNoShortIf::TStatementNoShortIf(): Tree(NonTerminalType::StatementNoShortIf), v(TStatementNoShortIfV::Max), forStatementNoShortIf(nullptr), whileStatementNoShortIf(nullptr), statementWithoutTrailingSubstatement(nullptr), ifThenElseStatementNoShortIf(nullptr) {}

TStatementWithoutTrailingSubstatement::TStatementWithoutTrailingSubstatement(): Tree(NonTerminalType::StatementWithoutTrailingSubstatement), v(TStatementWithoutTrailingSubstatementV::Max), returnStatement(nullptr), block(nullptr), expressionStatement(nullptr) {}

TStringLiteral::TStringLiteral(): Tree(NonTerminalType::StringLiteral), v(TStringLiteralV::Max) {}

TThis2::TThis2(): Tree(NonTerminalType::This2), v(TThis2V::Max) {}

TType::TType(): Tree(NonTerminalType::Type), v(TTypeV::Max), referenceType(nullptr), primitiveType(nullptr) {}

TTypeDeclaration::TTypeDeclaration(): Tree(NonTerminalType::TypeDeclaration), v(TTypeDeclarationV::Max), interfaceDeclaration(nullptr), classDeclaration(nullptr) {}

TTypeImportOnDemandDeclaration::TTypeImportOnDemandDeclaration(): Tree(NonTerminalType::TypeImportOnDemandDeclaration), v(TTypeImportOnDemandDeclarationV::Max), name(nullptr) {}

TUnaryExpression::TUnaryExpression(): Tree(NonTerminalType::UnaryExpression), v(TUnaryExpressionV::Max), unaryExpressionNotPlusMinus(nullptr), unaryExpression(nullptr) {}

TUnaryExpressionNotPlusMinus::TUnaryExpressionNotPlusMinus(): Tree(NonTerminalType::UnaryExpressionNotPlusMinus), v(TUnaryExpressionNotPlusMinusV::Max), castExpression(nullptr), unaryExpression(nullptr), primary(nullptr), name(nullptr) {}

TVariableDeclaration::TVariableDeclaration(): Tree(NonTerminalType::VariableDeclaration), v(TVariableDeclarationV::Max), type(nullptr), variableDeclarator(nullptr) {}

TVariableDeclarator::TVariableDeclarator(): Tree(NonTerminalType::VariableDeclarator), v(TVariableDeclaratorV::Max), expression(nullptr), identifier(nullptr) {}

TWhileStatement::TWhileStatement(): Tree(NonTerminalType::WhileStatement), v(TWhileStatementV::Max), expression(nullptr), statement(nullptr) {}

TWhileStatementNoShortIf::TWhileStatementNoShortIf(): Tree(NonTerminalType::WhileStatementNoShortIf), v(TWhileStatementNoShortIfV::Max), expression(nullptr), statementNoShortIf(nullptr) {}

} // namespace Parse 
