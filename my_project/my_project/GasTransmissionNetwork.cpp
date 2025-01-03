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
		std::cout << "��� ���������������� ���� ������������ ������������� �������\n";
		return;
	}
	if (check->getOnly01("������� ��������� �������� �������������� ���������?\n0 - ���\n1 - ��\n")) {
		std::cout << cc->showCompressorComplex();
	}
	int idInput = check->checkInputInt("������� �������������� ��-�����\n", false);
	int idOutput = check->checkInputInt("������� �������������� ��-������\n", false);
	if (cc->count(idInput) and cc->count(idOutput)) {
		int diameter = check->makeInputFromVector("������� ������� ����� (500,700,1000 ��� 1400 ��)\n", false, { 500,700,1000,1400 });
		std::vector<int> ids = pipeline->findDiameterForNetwork(diameter);
		std::cout << std::endl;
		if (ids.size() > 0) {
			for (int id : ids) {
				std::cout << pipeline->showElement(id) << std::endl;
			}
			std::cout << std::endl;
			int pipeId = check->makeInputFromVector("�������� ���������� �����\n", false, ids);
			pipeline->getAJobForPipe(pipeId,idInput,idOutput);
		}
		else {
			std::cout << "��� ��� ���������� ����� �� �������, �� �������� �����\n";
			Pipe pipe(*check);
			pipe.setName(check->checkInputString("������� �������� �����\n"));
			pipe.setLength(check->checkInputInt("������� ����� ����� � ����������\n", true));
			pipe.setDiameter(diameter);
			pipe.setUnderRepair();
			pipe.getAJob(idInput, idOutput);
			pipeline->setPipeline(pipe);
		}
		std::cout << "������!\n";
	}
	else {
		std::cout << "������ � �������� ���������������\n";
	}

}