#pragma once

#include "cell.h"
#include "common.h"

#include <functional>

class Sheet : public SheetInterface {
public:
	Sheet() {
		table_.resize(1);
		table_[0].resize(1);
	}
    ~Sheet();

    void SetCell(Position pos, std::string text) override;

    const CellInterface* GetCell(Position pos) const override;
    CellInterface* GetCell(Position pos) override;

    void ClearCell(Position pos) override;

    Size GetPrintableSize() const override;

    void PrintValues(std::ostream& output) const override;
    void PrintTexts(std::ostream& output) const override;

	//std::vector<Position> GetDependentCells();
	//std::vector<Position> GetReferencedCells();	


private:
	enum PositionValidity {
		READ,
		WRITE,
	};

	bool CheckPositionValidity(Position pos, PositionValidity key) const;

	// Можете дополнить ваш класс нужными полями и методами
	std::vector<std::vector<std::unique_ptr<Cell>>> table_;
    //Size printable_size_;
	std::vector<int> existing_cols_{ 0 };
	std::vector<int> existing_rows_{ 0 };
};

struct OstreamCellPrinter {
	std::ostream& out;

	void operator()(std::string str) const {
		out << str;
	}
	void operator()(double val) const {
		out << val;
	}
	void operator()(FormulaError er) const {
		out << er;
	}
};
