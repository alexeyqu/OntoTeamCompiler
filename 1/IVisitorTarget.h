#pragma once

class IVisitor;

class IVisitorTarget
{
public:
   	virtual void Accept( IVisitor* ) = 0;
};
