#pragma once
#include "IAppBase.h"
class AppWorker : public IAppBase {
public:
	AppWorker(): IAppBase("AppWorkerBase00")  {
		printf("AppWorker()\n");
	};
	~AppWorker() override {
		printf("~AppWorker(),interface name:{AppWorker}\n");
	}
	virtual void work() {
		printf("AppWorker : I'm fucking works\n");
	}
private:
};