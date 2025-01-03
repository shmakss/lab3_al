#include "GasTransmissionNetwork.h"


GasTransmissionNetwork::GasTransmissionNetwork(CheckInput& check, Pipeline& pipeline, CompressorComplex& cc)
{
	this->check = &check;
	this->pipeline = &pipeline;
	this->cc = &cc;
}


void GasTransmissionNetwork::join()
{
	
	if (cc->size() < 2) {
		std::cout << "Для газотранспортной сети недостаточно компрессорных станций\n";
		return;
	}
	if (check->getOnly01("Вывести доступные элементы компрессорного комплекса?\n0 - нет\n1 - да\n")) {
		std::cout << cc->showCompressorComplex();
	}
	int idInput = check->checkInputInt("Введите индентификатор КС-входа\n", false);
	int idOutput = check->checkInputInt("Введите индентификатор КС-выхода\n", false);
	if (cc->count(idInput) and cc->count(idOutput)) {
		int diameter = check->makeInputFromVector("Введите диаметр трубы (500,700,1000 или 1400 мм)\n", false, { 500,700,1000,1400 });
		std::vector<int> ids = pipeline->findDiameterForNetwork(diameter);
		std::cout << std::endl;
		if (ids.size() > 0) {
			for (int id : ids) {
				std::cout << pipeline->showElement(id) << std::endl;
			}
			std::cout << std::endl;
			int pipeId = check->makeInputFromVector("Выберите подходящую трубу\n", false, ids);
			pipeline->getAJobForPipe(pipeId,idInput,idOutput);
		}
		else {
			std::cout << "Так как подходящей трубы не нашлось, мы создадим новую\n";
			Pipe pipe(*check);
			pipe.setName(check->checkInputString("Введите название трубы\n"));
			pipe.setLength(check->checkInputInt("Введите длину трубы в километрах\n", true));
			pipe.setDiameter(diameter);
			pipe.setUnderRepair();
			pipe.getAJob(idInput, idOutput);
			pipeline->setPipeline(pipe);
		}
		std::cout << "Готово!\n";
	}
	else {
		std::cout << "Ошибка в введённом индентификаторе\n";
	}

}