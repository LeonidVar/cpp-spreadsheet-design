#pragma once

#include "FormulaLexer.h"
#include "common.h"

#include <forward_list>
#include <functional>
#include <stdexcept>

namespace ASTImpl {
class Expr;


class CellExpr : public Expr {
public: 
    // FormulaAST ����� ��������� �������� ��� �������� CELL �����
    // ���������� ������� �� ������ Evaluate(const SheetInterface& sheet) formula.cpp 
    // ������� ����� ��������� �������� ���: sheet.GetCell->GetValue
    double Evaluate(const std::function<double(Position)>& func) {
        return func(value_);
    }
private:
    Position value_;

};
}

class ParsingError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class FormulaAST {
public:
    explicit FormulaAST(std::unique_ptr<ASTImpl::Expr> root_expr);
    FormulaAST(FormulaAST&&) = default;
    FormulaAST& operator=(FormulaAST&&) = default;
    ~FormulaAST();

    // ������������� ������� � Evaluate()
    double Execute(const std::function<double(Position)>& func) const;
    void Print(std::ostream& out) const;
    void PrintFormula(std::ostream& out) const;

private:
    std::unique_ptr<ASTImpl::Expr> root_expr_;
    std::forward_list<Position> cells_;
};

FormulaAST ParseFormulaAST(std::istream& in);
FormulaAST ParseFormulaAST(const std::string& in_str);