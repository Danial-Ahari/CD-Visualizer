#include "../include/mainwindow.hpp"
#include <iostream>
#include <fcntl.h>

int8_t ecmify(uint8_t* insector);
void eccedc_init(void);
bool sectorArray[330000];

MainWindow::MainWindow()
: instruction_label("Below is a block diagram. Each block represents up to 33000 sectors.")
{
	FILE *image = fopen("test.bin", "rb+");
	createSectorArray(image);
	set_border_width(10);
	add(main_grid);
	main_grid.attach(instruction_label,0,0,10);
	main_grid.attach(sector_button_0,0,1,1);
	main_grid.attach(sector_button_1,1,1,1);
	main_grid.attach(sector_button_2,2,1,1);
	main_grid.attach(sector_button_3,3,1,1);
	main_grid.attach(sector_button_4,4,1,1);
	main_grid.attach(sector_button_5,5,1,1);
	main_grid.attach(sector_button_6,6,1,1);
	main_grid.attach(sector_button_7,7,1,1);
	main_grid.attach(sector_button_8,8,1,1);
	main_grid.attach(sector_button_9,9,1,1);
	sector_button_0.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_0_button_clicked));
	sector_button_1.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_1_button_clicked));
	sector_button_2.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_2_button_clicked));
	sector_button_3.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_3_button_clicked));
	sector_button_4.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_4_button_clicked));
	sector_button_5.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_5_button_clicked));
	sector_button_6.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_6_button_clicked));
	sector_button_7.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_7_button_clicked));
	sector_button_8.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_8_button_clicked));
	sector_button_9.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_9_button_clicked));
	sector_button_0.set_size_request(100,100);
	sector_button_1.set_size_request(100,100);
	sector_button_2.set_size_request(100,100);
	sector_button_3.set_size_request(100,100);
	sector_button_4.set_size_request(100,100);
	sector_button_5.set_size_request(100,100);
	sector_button_6.set_size_request(100,100);
	sector_button_7.set_size_request(100,100);
	sector_button_8.set_size_request(100,100);
	sector_button_9.set_size_request(100,100);
	instruction_label.show();
	updateLevel();
	main_grid.show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_0_button_clicked() {
	on_sector_clicked(0);
}
void MainWindow::on_1_button_clicked() {
	on_sector_clicked(1);
}
void MainWindow::on_2_button_clicked() {
	on_sector_clicked(2);
}
void MainWindow::on_3_button_clicked() {
	on_sector_clicked(3);
}
void MainWindow::on_4_button_clicked() {
	on_sector_clicked(4);
}
void MainWindow::on_5_button_clicked() {
	on_sector_clicked(5);
}
void MainWindow::on_6_button_clicked() {
	on_sector_clicked(6);
}
void MainWindow::on_7_button_clicked() {
	on_sector_clicked(7);
}
void MainWindow::on_8_button_clicked() {
	on_sector_clicked(8);
}
void MainWindow::on_9_button_clicked() {
	on_sector_clicked(9);
}

void MainWindow::on_sector_clicked(int button) {
	levelsOfView++;
	if(levelsOfView == 1) {

		targetLocationLevel1 = button;
	} else if(levelsOfView == 2) {

		targetLocationLevel2 = button;
	} else if(levelsOfView == 3) {

		targetLocationLevel3 = button;
	} else if(levelsOfView == 4) {

		targetLocationLevel4 = button;
	} else if(levelsOfView == 5) {

		targetLocationLevel5 = button;
	} else if(levelsOfView == 6) {
		levelsOfView = 0;
		targetLocationLevel1 = 0;
		targetLocationLevel2 = 0;
		targetLocationLevel3 = 0;
		targetLocationLevel4 = 0;
		targetLocationLevel5 = 0;
	}
	updateLevel();
}

void MainWindow::updateLevel() {
	std::cout << levelsOfView;
	if(levelsOfView == 0) {
		instruction_label.set_text("Below is a block diagram. Each block represents up to 33000 sectors.");
		renderBlocks(0);
	} else if(levelsOfView == 1) {
		instruction_label.set_text("Below is a block diagram. Each block represents up to 3300 sectors.");
		renderBlocks(1);
	}  else if(levelsOfView == 2) {
		instruction_label.set_text("Below is a block diagram. Each block represents up to 330 sectors.");
		renderBlocks(2);
	} else if(levelsOfView == 3) {
		instruction_label.set_text("Below is a block diagram. Each block represents up to 33 sectors.");
		renderBlocks(3);
	} else if(levelsOfView == 4) {
		instruction_label.set_text("Below is a block diagram. Each block represents up to 10 sectors, except for the last which always represents 3.");
		renderBlocks(4);
	} else if(levelsOfView == 5) {
		instruction_label.set_text("Below is a block diagram. Each block represents a sector.");
		renderBlocks(5);
	}
}

void MainWindow::createSectorArray(FILE* image) {
	fseek(image, 0, SEEK_END);
	numOfSectors = ftell(image)/2352;
	fseek(image, 0, SEEK_SET);
	eccedc_init();
	for(int i = 0; i < numOfSectors; i++) {
		uint8_t * Buf = (uint8_t*)malloc(sizeof(uint8_t)*2352);
		fread(Buf, 1, 2352, image);
		int resultEC = ecmify(Buf);
		if(resultEC == 0) {
			sectorArray[i] = false;
		} else {
			sectorArray[i] = true;
		}
		free(Buf);
	}
}

std::string MainWindow::testSectors(int first, int last) {
	int errors = 0;
	for(int i = first; i <= last ; i++) {
		if(sectorArray[i]) {
			errors++;
		}
		if(i == numOfSectors) {
			break;
		}
	}
	if(errors > 49) {
		return "Bad\n";
	} else if (errors > 0) {
		return "Errored\n";
	}
	return "Good\n";
}

std::string MainWindow::makeString(int first, int last) {
	if(levelsOfView < 2) {
		float f_first = (float)first/1000;
		float f_last = (float)last/1000;
		return std::to_string(f_first).substr(0,4) + "k-" + std::to_string(f_last).substr(0,4) + "k";
	} else {
		return std::to_string(first) + "-" + std::to_string(last);
	}
}

void MainWindow::renderBlocks(int level) {
	int loc1 = 33000*targetLocationLevel1;
	int loc2 = 3300*targetLocationLevel2;
	int loc3 = 330*targetLocationLevel3;
	int loc4 = 33*targetLocationLevel4;
	int loc5 = 10*targetLocationLevel5;
	int loc;
	int diff;
	
	switch(level) {
		case 1:
			loc = loc1;
			diff = 3300;
			break;
		case 2:
			loc = loc1 + loc2;
			diff = 330;
			break;
		case 3:
			loc = loc1 + loc2 + loc3;
			diff = 33;
			break;
		case 4:
			loc = loc1 + loc2 + loc3 + loc4;
			diff = 10;
			break;
		case 5:
			loc = loc1 + loc2 + loc3 + loc4 + loc5;
			diff = 1;
			break;
		default:
			loc = 0;
			diff = 33000;
			break;
	}
	
	if(numOfSectors > loc) {
		sector_button_0.set_label(testSectors(loc, loc+diff) + makeString(loc, loc+diff));
		sector_button_0.show();
	}
	if(numOfSectors > loc+diff) {
		sector_button_1.set_label(testSectors(loc+diff+1, loc+(2*diff)) + makeString(loc+diff+1, loc+(2*diff)));
		sector_button_1.show();
	} else {
		sector_button_1.hide();
	}
	if(numOfSectors > loc+(2*diff)) {
		sector_button_2.set_label(testSectors(loc+(2*diff)+1, loc+(3*diff)) + makeString(loc+(2*diff)+1, loc+(3*diff)));
		sector_button_2.show();
	} else {
		sector_button_2.hide();
	}
	if(numOfSectors > loc+(3*diff)) {
		sector_button_3.set_label(testSectors(loc+(3*diff)+1, loc+(4*diff)) + makeString(loc+(3*diff)+1, loc+(4*diff)));
		sector_button_3.show();
	} else {
		sector_button_3.hide();
	}
	if(numOfSectors > loc+(4*diff)) {
		sector_button_4.set_label(testSectors(loc+(4*diff)+1, loc+(5*diff)) + makeString(loc+(4*diff)+1, loc+(5*diff)));
		sector_button_4.show();
	} else {
		sector_button_4.hide();
	}
	if(numOfSectors > loc+(5*diff)) {
		sector_button_5.set_label(testSectors(loc+(5*diff)+1, loc+(6*diff)) + makeString(loc+(5*diff)+1, loc+(6*diff)));
		sector_button_5.show();
	} else {
		sector_button_5.hide();
	}
	if(numOfSectors > loc+(6*diff)) {
		sector_button_6.set_label(testSectors(loc+(6*diff)+1, loc+(7*diff)) + makeString(loc+(6*diff)+1, loc+(7*diff)));
		sector_button_6.show();
	} else {
		sector_button_6.hide();
	}
	if(numOfSectors > loc+(7*diff)) {
		sector_button_7.set_label(testSectors(loc+(7*diff)+1, loc+(8*diff)) + makeString(loc+(7*diff)+1, loc+(8*diff)));
		sector_button_7.show();
	} else {
		sector_button_7.hide();
	}
	if(numOfSectors > loc+(8*diff)) {
		sector_button_8.set_label(testSectors(loc+(8*diff)+1, loc+(9*diff)) + makeString(loc+(8*diff)+1, loc+(9*diff)));
		sector_button_8.show();
	} else {
		sector_button_8.hide();
	}
	if(numOfSectors > loc+(9*diff)) {
		sector_button_9.set_label(testSectors(loc+(9*diff)+1, loc+(10*diff)) + makeString(loc+(9*diff)+1, loc+(10*diff)));
		sector_button_9.show();
	} else {
		sector_button_9.hide();
	}
	
	if(level == 4) {
		sector_button_4.hide();
		sector_button_5.hide();
		sector_button_6.hide();
		sector_button_7.hide();
		sector_button_8.hide();
		sector_button_9.hide();
	}
}
