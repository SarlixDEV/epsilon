#ifndef GRAPH_VALUES_CONTROLLER_H
#define GRAPH_VALUES_CONTROLLER_H

#include <escher.h>
#include "../function_store.h"
#include "../evaluate_context.h"
#include "function_title_cell.h"
#include "value_cell.h"
#include "title_cell.h"
#include "interval.h"
#include "values_parameter_controller.h"

namespace Graph {

class ValuesController : public HeaderViewController, public TableViewDataSource {
public:
  ValuesController(Responder * parentResponder, FunctionStore * functionStore, EvaluateContext * evaluateContext);

  void setActiveCell(int i, int j);

  const char * title() const override;
  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;
  ViewController * parameterController();
  int numberOfButtons() const override;
  Button * buttonAtIndex(int index) override;

  int numberOfRows() override;
  int numberOfColumns() override;
  void willDisplayCellAtLocation(View * cell, int i, int j) override;
  KDCoordinate columnWidth(int i) override;
  KDCoordinate rowHeight(int j) override;
  KDCoordinate cumulatedWidthFromIndex(int i) override;
  KDCoordinate cumulatedHeightFromIndex(int j) override;
  int indexFromCumulatedWidth(KDCoordinate offsetX) override;
  int indexFromCumulatedHeight(KDCoordinate offsetY) override;
  View * reusableCell(int index, int type) override;
  int reusableCellCount(int type) override;
  int typeAtLocation(int i, int j) override;

  static constexpr KDCoordinate k_topMargin = 10;
  static constexpr KDCoordinate k_bottomMargin = 5;
  static constexpr KDCoordinate k_leftMargin = 1;
  static constexpr KDCoordinate k_rightMargin = 10;
  static constexpr KDCoordinate k_cellHeight = 30;
  static constexpr KDCoordinate k_abscissaCellWidth = 150;
  static constexpr KDCoordinate k_ordinateCellWidth = 100;

private:
  Responder * tabController() const;
  constexpr static int k_maxNumberOfCells = 40;
  constexpr static int k_maxNumberOfFunctions = 5;
  // !!! CAUTION: The order here is important
  // The cells should be initialized *before* the TableView!
  TitleCell m_abscissaTitleCell;
  FunctionTitleCell m_functionTitleCells[k_maxNumberOfFunctions];
  ValueCell m_floatCells[k_maxNumberOfCells];
  TableView m_tableView;
  int m_activeCellX;
  int m_activeCellY;
  FunctionStore * m_functionStore;
  EvaluateContext * m_evaluateContext;
  Interval m_interval;
  ValuesParameterController m_parameterController;
  Button m_setIntervalButton;
};

}

#endif
