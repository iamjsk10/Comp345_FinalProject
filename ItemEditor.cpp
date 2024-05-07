#include "ItemEditor.h"
#include <QStringList>
#include <QStringListModel>
ItemEditor::ItemEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.button_mainPage_newItem, SIGNAL(clicked()), this, SLOT(on_button_mainPage_newItem_clicked()));
	connect(ui.button_mainPage_exit, SIGNAL(clicked()), this, SLOT(on_button_mainPage_exit_clicked()));
	connect(ui.button_createItem_createAndSave, SIGNAL(clicked()), this, SLOT(on_button_createItem_createAndSave_clicked()));
	connect(ui.button_createItem_exit, SIGNAL(clicked()), this, SLOT(on_button_createItem_exit_clicked()));
	QStringListModel* model = new QStringListModel();
	QStringList itemTypes;
	itemTypes.append("Armor");
	itemTypes.append("Belt");
	itemTypes.append("Boots");
	itemTypes.append("Helmet");
	itemTypes.append("Ring");
	itemTypes.append("Shield");
	itemTypes.append("Weapon");
	model->setStringList(itemTypes);
	ui.list_createItem_itemType->setModel(model);
	model = new QStringListModel();
	QStringList enhancementTypes;
	enhancementTypes.append("intelligence");
	enhancementTypes.append("wisdom");
	enhancementTypes.append("armorClass");
	enhancementTypes.append("strength");
	enhancementTypes.append("constitution");
	enhancementTypes.append("charisma");
	enhancementTypes.append("dexterity");
	enhancementTypes.append("attackBonus");
	enhancementTypes.append("damageBonus");
	model->setStringList(enhancementTypes);
	ui.list_createItem_enhancement->setModel(model);
}

ItemEditor::~ItemEditor()
{}

void ItemEditor::on_button_mainPage_newItem_clicked() {
	ui.stackedWidget->setCurrentWidget(ui.widget_createItem);
};
void ItemEditor::on_button_mainPage_exit_clicked() {
	close();
};

void ItemEditor::on_button_createItem_createAndSave_clicked() {
	QModelIndexList itemTypeIndex = ui.list_createItem_itemType->selectionModel()->selectedIndexes();
	if (itemTypeIndex.isEmpty()) {
		qDebug() << "No Item Type selected";
		return;
	}
	QModelIndex selectedIndex = itemTypeIndex.first();
	QVariant selectedItemData = selectedIndex.data(Qt::DisplayRole); // Assuming DisplayRole is used for displaying item data
	int itemNumber = selectedIndex.row();
	QModelIndexList enhancementTypeIndex = ui.list_createItem_enhancement->selectionModel()->selectedIndexes();
	if (itemTypeIndex.isEmpty()) {
		qDebug() << "No enhacnement selected";
		return;
	}
	selectedIndex = enhancementTypeIndex.first();
	QVariant selectedEnhancementData = selectedIndex.data(Qt::DisplayRole); // Assuming DisplayRole is used for displaying item data
	int enhancementNumber = selectedIndex.row();
	EnhancementType enhancementType;
	switch (enhancementNumber) {
	case 0:
		enhancementType = EnhancementType::intelligence;
		break;
	case 1:
		enhancementType = EnhancementType::wisdom;
		break;
	case 2:
		enhancementType = EnhancementType::armorClass;
		break;
	case 3:
		enhancementType = EnhancementType::strength;
		break;
	case 4:
		enhancementType = EnhancementType::constitution;
		break;
	case 5:
		enhancementType = EnhancementType::charisma;
		break;
	case 6:
		enhancementType = EnhancementType::dexterity;
		break;
	case 7:
		enhancementType = EnhancementType::attackBonus;
		break;
	case 8:
		enhancementType = EnhancementType::damageBonus;
		break;
	}
	string itemName = ui.input_createItem_name->text().toStdString();
	int enhancementBonus = ui.input_createItem_enhancementBonus->value();
	if (enhancementBonus <= 0 || enhancementBonus > 5) {
		qDebug() << "Invalid bonus";
		return;
	}
	Item* item;
	switch (itemNumber) {
	case 0:
		item = new Armor(itemName, enhancementType, enhancementBonus);
		return;
		break;
	case 1:
		item = new Belt(itemName, enhancementType, enhancementBonus);
		break;
	case 2:
		item = new Boots(itemName, enhancementType, enhancementBonus);
		break;
	case 3:
		item = new Helmet(itemName, enhancementType, enhancementBonus);
		break;
	case 4:
		item = new Ring(itemName, enhancementType, enhancementBonus);
		break;
	case 5:
		item = new Shield(itemName, enhancementType, enhancementBonus);
		break;
	case 6:
		item = new Weapon(itemName, enhancementType, enhancementBonus);
		break;
	}
	qDebug() << "Item created";
	saveItem(item);
	qDebug() << "Item saved";

};
void ItemEditor::on_button_createItem_exit_clicked() {
	close();

};