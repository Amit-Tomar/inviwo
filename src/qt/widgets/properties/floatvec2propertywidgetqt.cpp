/**********************************************************************
 * Copyright (C) 2013 Scientific Visualization Group - Link�ping University
 * All Rights Reserved.
 * 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * No part of this software may be reproduced or transmitted in any
 * form or by any means including photocopying or recording without
 * written permission of the copyright owner.
 *
 * Primary author : Alexander Johansson
 *
 **********************************************************************/

#include <inviwo/qt/widgets/properties/floatvec2propertywidgetqt.h>
#include <QHBoxLayout>
#include <QLabel>

namespace inviwo {

FloatVec2PropertyWidgetQt::FloatVec2PropertyWidgetQt(FloatVec2Property *property)
    : property_(property)
    , settingsWidget_(0) 
    , valueVec2Max_(property->getMaxValue())
    , valueVec2Min_(property->getMinValue())
    , valueIncrement_(property->getIncrement()) {
        
    PropertyWidgetQt::setProperty(property_);
    PropertyWidgetQt::generateContextMenu();
	generateWidget();
	updateFromProperty();
    if(!property->getReadOnly())
        generatesSettingsWidget();
}

FloatVec2PropertyWidgetQt::~FloatVec2PropertyWidgetQt(){
    settingsWidget_->deleteLater();
}

void FloatVec2PropertyWidgetQt::generateWidget() {
	QHBoxLayout* hLayout = new QHBoxLayout();
    if (property_->getReadOnly()) {
        valueVec_ = property_->get();
        hLayout->addWidget(new QLabel(QString::fromStdString(property_->getDisplayName())));
        readOnlyLabel_ = new QLabel();
        hLayout->addWidget(readOnlyLabel_);
        setLayout(hLayout);
    }
    else{
        label_ = new EditableLabelQt(this,property_->getDisplayName(),PropertyWidgetQt::generatePropertyWidgetMenu());
        hLayout->addWidget(label_);

	    QWidget* sliderWidget = new QWidget();
	    QVBoxLayout* vLayout = new QVBoxLayout();
	    sliderWidget->setLayout(vLayout);

        
        sliderX_ = new FloatSliderWidgetQt();
        sliderY_ = new FloatSliderWidgetQt();

	    vLayout->addWidget(sliderX_);
	    vLayout->addWidget(sliderY_);
        vLayout->setContentsMargins(0,0,0,0);
        vLayout->setSpacing(0);
	    hLayout->addWidget(sliderWidget);
	    setLayout(hLayout);

        QSizePolicy labelPol = label_->sizePolicy();
        labelPol.setHorizontalStretch(1);
        labelPol.setControlType(QSizePolicy::Label);
        label_->setSizePolicy(labelPol);

        QSizePolicy slidersPol = sliderWidget->sizePolicy();
        slidersPol.setHorizontalStretch(3);
        sliderWidget->setSizePolicy(slidersPol);

        connect(sliderX_, SIGNAL(valueChanged(float)), this, SLOT(setPropertyValue()));
        connect(sliderY_, SIGNAL(valueChanged(float)), this, SLOT(setPropertyValue()));
        connect(label_, SIGNAL(textChanged()),this, SLOT(setPropertyDisplayName()));

    }
}

void FloatVec2PropertyWidgetQt::updateFromProperty() {
    valueVec_ = property_->get();
    if (property_->getReadOnly()) {
        readOnlyLabel_->setText(QString::number(valueVec_.x)+ " , " +QString::number(valueVec_.y));
        readOnlyLabel_->setToolTip("Min: [" +QString::number((property_->getMinValue()).x)+","+QString::number((property_->getMinValue()).y)+
            "] Max: [" +QString::number((property_->getMaxValue()).x)+","+QString::number((property_->getMaxValue()).y)+"]");
       
    }
    else {
        valueVec2Max_ = property_->getMaxValue();
        valueVec2Min_ = property_->getMinValue();
        valueIncrement_ = property_->getIncrement();
        sliderX_->initValue(valueVec_.x);
        sliderY_->initValue(valueVec_.y);

        sliderX_->setRange(valueVec2Min_.x,valueVec2Max_.x);
        sliderY_->setRange(valueVec2Min_.y,valueVec2Max_.y);
        
        sliderX_->setValue(valueVec_.x);
        sliderY_->setValue(valueVec_.y);

        sliderX_->setIncrement(valueIncrement_.x);
        sliderY_->setIncrement(valueIncrement_.y);
    }
}


void FloatVec2PropertyWidgetQt::generatesSettingsWidget() {
    settingsWidget_ = new PropertySettingsWidgetQt(property_);

    settingsMenu_ = PropertyWidgetQt::generatePropertyWidgetMenu();
    settingsMenu_->addAction("Property settings");
    settingsMenu_->addAction("Set as Min");
    settingsMenu_->addAction("Set as Max");

    sliderX_->setContextMenuPolicy(Qt::CustomContextMenu);
    sliderY_->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(sliderX_,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(showContextMenuX(const QPoint&)));
    connect(sliderY_,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(showContextMenuY(const QPoint&)));
     
    connect(developerViewModeAction_,SIGNAL(triggered(bool)),this, SLOT(setDeveloperViewMode(bool)));
    connect(applicationViewModeAction_,SIGNAL(triggered(bool)),this, SLOT(setApplicationViewMode(bool)));

    updateContextMenu();
  
}

void FloatVec2PropertyWidgetQt::showContextMenuX( const QPoint& pos ) {
    PropertyVisibilityMode appVisibilityMode  = getApplicationViewMode();
    if (appVisibilityMode == DEVELOPMENT) {
        updateContextMenu();
        QPoint globalPos = sliderX_->mapToGlobal(pos);
        QAction* selecteditem = settingsMenu_->exec(globalPos);
        if (selecteditem && selecteditem->text() == "Property settings") {
            settingsWidget_->reload();
            settingsWidget_->show();
        }
        else if (selecteditem && selecteditem->text() == "Set as Min") {
            //Set current value of the slider to min value of the property
            valueVec2Min_ = property_->getMinValue();
            valueVec2Min_.x = sliderX_->getValue();
            property_->setMinValue(valueVec2Min_);
            updateFromProperty();
        }
        else if (selecteditem && selecteditem->text() == "Set as Max"){
            //Set current value of the slider to max value of the property
            valueVec2Max_ = property_->getMaxValue();
            valueVec2Max_.x = sliderX_->getValue();
            property_->setMaxValue(valueVec2Max_);
            updateFromProperty();
        }
    }
}

void FloatVec2PropertyWidgetQt::showContextMenuY( const QPoint& pos ) {
    PropertyVisibilityMode appVisibilityMode  = getApplicationViewMode();
    if (appVisibilityMode == DEVELOPMENT) {
        updateContextMenu();
        QPoint globalPos = sliderY_->mapToGlobal(pos);        
        QAction* selecteditem = settingsMenu_->exec(globalPos);
        if (selecteditem && selecteditem->text() == "Property settings") {
            settingsWidget_->reload();
            settingsWidget_->show();
        }
        else if (selecteditem && selecteditem->text() == "Set as Min") {
            //Set current value of the slider to min value of the property
            valueVec2Min_ = property_->getMinValue();
            valueVec2Min_.y = sliderY_->getValue();
            property_->setMinValue(valueVec2Min_);
            updateFromProperty();
        }
        else if (selecteditem && selecteditem->text() == "Set as Max"){
            //Set current value of the slider to max value of the property
            valueVec2Max_ = property_->getMaxValue();
            valueVec2Max_.y = sliderY_->getValue();
            property_->setMaxValue(valueVec2Max_);
            updateFromProperty();
        }
    }
}

void FloatVec2PropertyWidgetQt::setPropertyValue() {
    valueVec_ = property_->get();
    valueVec_.x = sliderX_->getValue();
    valueVec_.y = sliderY_->getValue();
    property_->set(valueVec_);
    emit modified();
}

void FloatVec2PropertyWidgetQt::setPropertyDisplayName(){
    property_->setDisplayName(label_->getText());
}


} //namespace