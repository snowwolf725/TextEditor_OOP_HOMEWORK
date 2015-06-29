#include "StepHandler.h"
#include <iostream>

StepHandler *StepHandler::po=NULL;

StepHandler::StepHandler()
{

}

StepHandler *StepHandler::getInstance()
{
	if(po==NULL)po=new StepHandler();
	return po;
}

StepHandler::~StepHandler()
{
	
}

void StepHandler::setText(Text *text)
{
	m_pText=text;
}

void StepHandler::setCursor(Cursor *c)
{
	m_pCursor=c;
}

void StepHandler::setChecker(SpellChecker *sc)
{
	m_pSpellChecker=sc;
}

Step StepHandler::getCurrentStep()
{
	Step CurrentStep=Step(m_pCursor,m_pText,m_pSpellChecker);
	CurrentStep.saveState();
	return CurrentStep;
}

void StepHandler::saveStep()
{
//	cout<<"save to undostack "<<undoStack.size()<<","<<redoStack.size()<<endl;
	m_pStep=new Step(m_pCursor,m_pText,m_pSpellChecker);
	m_pStep->saveState();
	undoStack.push(*m_pStep);
//	cout<<"save to undostack "<<undoStack.size()<<","<<redoStack.size()<<endl;
}

void StepHandler::loadUndoStack()
{
//	cout<<"load undostack "<<undoStack.size()<<","<<redoStack.size()<<endl;
	if(undoStack.empty()==false)
	{
		//push redo stack
		m_pStep->saveState();
		redoStack.push(*m_pStep);
		
		//pop undo stack
		*m_pStep=undoStack.top();
		undoStack.pop();
		m_pStep->loadState();
	}
//	cout<<"load undostack "<<undoStack.size()<<","<<redoStack.size()<<endl;
}

void StepHandler::loadRedoStack()
{
//	cout<<"load redostack "<<undoStack.size()<<","<<redoStack.size()<<endl;
	if(redoStack.empty()==false)
	{
		//push redo stack
		m_pStep->saveState();
		undoStack.push(*m_pStep);
		
		//pop undo stack
		*m_pStep=redoStack.top();
		redoStack.pop();
		m_pStep->loadState();
	}
//	cout<<"load redostack "<<undoStack.size()<<","<<redoStack.size()<<endl;
}

void StepHandler::clearUndoStack()
{
//	cout<<"clear undostack "<<undoStack.size()<<","<<redoStack.size()<<endl;
	while(undoStack.empty()==false)
		undoStack.pop();
//	cout<<"clear undostack "<<undoStack.size()<<","<<redoStack.size()<<endl;
}

void StepHandler::clearRedoStack()
{
//	cout<<"clear redostack "<<undoStack.size()<<","<<redoStack.size()<<endl;
	while(redoStack.empty()==false)
		redoStack.pop();
//	cout<<"clear redostack "<<undoStack.size()<<","<<redoStack.size()<<endl;
}
