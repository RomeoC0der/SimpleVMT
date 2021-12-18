#pragma once
#include <iostream>
class IAppBase {
public:
	virtual ~ IAppBase() {
		printf("~IAppBase(),interface name:{%s}\n", szInterfaceName);
	}
	virtual IAppBase* queryInterface() {
		return this;
	}
	virtual void debugPrint() {
		printf("It is a debug output\n");
	}
	IAppBase(const char* szAppName) {
		this->szInterfaceName = szAppName;
		printf("IAppBase(szAppName)\n");
	}
private:
	const char* szInterfaceName{ nullptr };
};