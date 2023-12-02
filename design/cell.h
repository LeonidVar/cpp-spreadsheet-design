#pragma once

#include "common.h"
#include "formula.h"

class Sheet;

class Impl {
public:
    virtual ~Impl() = default;
    virtual CellInterface::Value GetValue() const;
    virtual std::string GetText() const;
};

class EmptyImpl : public Impl {
public:
    EmptyImpl() = default;
};

class TextImpl : public Impl {
public:
    TextImpl(std::string text) : data_(text) {};
    ~TextImpl() = default;

    //void Set(std::string text);
    //void Clear();

    CellInterface::Value GetValue() const override;
    std::string GetText() const override;
private:
    std::string data_;
};
class FormulaImpl : public Impl {
public:
    FormulaImpl(std::string text, SheetInterface& sheet)
        : data_(ParseFormula(text)), sheet_(sheet) {}
    
    ~FormulaImpl() = default;

    //void Set(std::string text);
    //void Clear();

    CellInterface::Value GetValue() const override;
    std::string GetText() const override;
private:
    std::unique_ptr<FormulaInterface> data_;
    SheetInterface& sheet_;
    std::optional<double> cached_value_;
    std::vector<Position> referenced_cells_;
    std::vector<Position> dependent_cells_;
};


class Cell : public CellInterface {
public:
    Cell(SheetInterface& sheet)
        : sheet_(sheet) {}
    ~Cell();

    void Set(std::string text);
    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;
    std::vector<Position> GetReferencedCells() const override;
    std::vector<Position> GetDependentCells();
    bool CheckCyclicDependence();

private:
    std::unique_ptr<Impl> impl_;
    SheetInterface& sheet_;

};