#include <QPushButton>
#include <QMenu>
#include <QWidgetAction>
#include <QHeaderView>
#include <QDebug>

#include "model/Node.h"
#include "FlowView.h"
#include "../model/output/MasterMaterialOutput.h"

namespace ShaderGraph
{
    FlowView::FlowView(QWidget *parent) : QtNodes::FlowView(parent)
    {
        connect(this->scene(), &QtNodes::FlowScene::nodeDeleted,
                this, &::ShaderGraph::FlowView::onNodeDeleted);
    }

    FlowView::FlowView(QtNodes::FlowScene *scene, QWidget *parent) : QtNodes::FlowView(scene, parent)
    {
        connect(this->scene(), &QtNodes::FlowScene::nodeDeleted,
                this, &::ShaderGraph::FlowView::onNodeDeleted);
    }






    void FlowView::onNodeDeleted(QtNodes::Node& n)
    {
        Q_UNUSED(n);

        ShaderGraph::Node * node;

        bool isDeletingTheDetailedNode = false;

        // Check if the MasterMaterialOutputNode is in the selectedItems.
        // If it is, then "cancel" this event, else continue.
        for (QGraphicsItem * item : scene()->selectedItems())
        {
            auto nodeGraphicsObject = qgraphicsitem_cast<QtNodes::NodeGraphicsObject*>(item);

            if (nodeGraphicsObject)
            {
              node = dynamic_cast<ShaderGraph::Node*>(nodeGraphicsObject->node().nodeDataModel());

              assert(node);

                isDeletingTheDetailedNode |= node->isDetailedNode();
            }
        }

        if (isDeletingTheDetailedNode) m_detailedNode = nullptr;
    }









    void FlowView::mousePressEvent(QMouseEvent * event)
    {
        std::vector<QtNodes::Node*> nodes = scene()->selectedNodes();

        if (nodes.empty())
        {
            if (m_detailedNode) m_detailedNode->hideDetails(m_detailsTree);
            m_detailedNode = nullptr;
        }
        else
        {
            bool hasPromotedNode = false;

            for (QtNodes::Node * node : nodes)
            {
                auto sgNode = dynamic_cast<ShaderGraph::Node *>(node->nodeDataModel());

                if (sgNode == nullptr) // cast failed
                {
                    LOG_ERROR("FlowView::mousePressEvent : Invalid node : Ignored");
                }
                else
                {
                    if (m_detailedNode) m_detailedNode->hideDetails(m_detailsTree);
                    m_detailedNode = sgNode;

                    sgNode->showDetails(m_detailsTree);

                    hasPromotedNode = true;
                }
            }

            if (!hasPromotedNode)
            {
                LOG_ERROR("FlowView::mousePressEvent : Any selected nodes has been promoted");
                m_detailedNode = nullptr;
            }
        }
        QtNodes::FlowView::mousePressEvent(event);
    }

    void FlowView::deleteSelectedNodes(){
        ShaderGraph::Node * node;
        for (QGraphicsItem * item : scene()->selectedItems())
        {
          if (auto n = qgraphicsitem_cast<QtNodes::NodeGraphicsObject*>(item)){
            node = static_cast<ShaderGraph::Node*>(n->node().nodeDataModel());
            if(node->name()==QStringLiteral("MasterMaterialOutput")){
              LOG_WARN("Cannot delete the MasterMaterialOutput");
              return;
            }
          }
        }
        QtNodes::FlowView::deleteSelectedNodes();
    }

    void
    FlowView::
    contextMenuEvent(QContextMenuEvent *event)
    {
      if (itemAt(event->pos()))
      {
        QGraphicsView::contextMenuEvent(event);
        return;
      }

      QMenu modelMenu;

      auto skipText = QStringLiteral("skip me");

      //Add filterbox to the context menu
      auto *txtBox = new QLineEdit(&modelMenu);

      txtBox->setPlaceholderText(QStringLiteral("Filter"));
      txtBox->setClearButtonEnabled(true);

      auto *txtBoxAction = new QWidgetAction(&modelMenu);
      txtBoxAction->setDefaultWidget(txtBox);

      modelMenu.addAction(txtBoxAction);

      //Add result treeview to the context menu
      auto *treeView = new QTreeWidget(&modelMenu);
      treeView->header()->close();

      auto *treeViewAction = new QWidgetAction(&modelMenu);
      treeViewAction->setDefaultWidget(treeView);

      modelMenu.addAction(treeViewAction);

      QMap<QString, QTreeWidgetItem*> topLevelItems;
      for (auto const &cat : scene()->registry().categories())
      {
        if(cat!=QStringLiteral("Output")){
          auto item = new QTreeWidgetItem(treeView);
          item->setText(0, cat);
          item->setData(0, Qt::UserRole, skipText);
          topLevelItems[cat] = item;
        }
      }

      for (auto const &assoc : scene()->registry().registeredModelsCategoryAssociation())
      {
        if(assoc.first!=QStringLiteral("MasterMaterialOutput")){
          auto parent = topLevelItems[assoc.second];
          auto item   = new QTreeWidgetItem(parent);
          item->setText(0, assoc.first);
          item->setData(0, Qt::UserRole, assoc.first);
        }
      }

      treeView->expandAll();

      connect(treeView, &QTreeWidget::itemClicked, [&](QTreeWidgetItem *item, int)
      {
        QString modelName = item->data(0, Qt::UserRole).toString();

        if (modelName == skipText)
        {
          return;
        }

        auto type = scene()->registry().create(modelName);

        if (type)
        {
          auto& node = scene()->createNode(std::move(type));

          QPoint pos = event->pos();

          QPointF posView = this->mapToScene(pos);

          node.nodeGraphicsObject().setPos(posView);

          scene()->nodePlaced(node);
        }
        else
        {
          qDebug() << "Model not found";
        }

        modelMenu.close();
      });

      //Setup filtering
      connect(txtBox, &QLineEdit::textChanged, [&](const QString &text)
      {
        for (auto& topLvlItem : topLevelItems)
        {
          for (int i = 0; i < topLvlItem->childCount(); ++i)
          {
            auto child = topLvlItem->child(i);
            auto modelName = child->data(0, Qt::UserRole).toString();
            const bool match = (modelName.contains(text, Qt::CaseInsensitive));
            child->setHidden(!match);
          }
        }
      });

      // make sure the text box gets focus so the user doesn't have to click on it
      txtBox->setFocus();

      modelMenu.exec(event->globalPos());
    }








}
