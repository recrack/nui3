/*
  NUI3 - C++ cross-platform GUI framework for OpenGL based applications
  Copyright (C) 2002-2003 Sebastien Metrot

  licence: see nui3/LICENCE.TXT
*/

#pragma once

#include "nuiMainWindow.h"
#include "nuiVBox.h"

class MainWindow : public nuiMainWindow
{
public:
  MainWindow(const nglContextInfo& rContext, const nglWindowInfo& rInfo, bool ShowFPS = false, const nglContext* pShared = NULL);
  ~MainWindow();

  void OnCreation();
  void OnClose();

protected:
  
  void Reset(const nuiEvent& rEvent);
  nuiWidget* BuildTabView(nuiPosition pos);
  
  void OnAddTab(const nuiEvent& rEvent);
  void OnRemoveTab(const nuiEvent& rEvent);
  
private:
  
  bool LoadCSS(const nglPath& rPath);

  nuiVBox* mpMainBox;
  nuiEventSink<MainWindow> mEventSink;
};

