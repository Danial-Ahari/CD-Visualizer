#include "../include/mainwindow.hpp"
#include <iostream>
#include <fcntl.h>
#include <iomanip>

int8_t ecmify(uint8_t* insector);
void eccedc_init(void);
bool sectorArray[330000];
bool threeSector;

MainWindow::MainWindow()
: instruction_label("Below is a block diagram. Each block represents up to 33000 sectors.")
{
	set_border_width(10);
	add(main_grid);
	main_grid.attach(instruction_label,0,1,5);
	main_grid.attach(error_label,5,1,4);
	main_grid.attach(reset_button,9,1,1);
	reset_button.set_label("Reset");
	reset_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::reset_vis));
	main_grid.attach(sector_button_0,0,2,1);
	main_grid.attach(sector_button_1,1,2,1);
	main_grid.attach(sector_button_2,2,2,1);
	main_grid.attach(sector_button_3,3,2,1);
	main_grid.attach(sector_button_4,4,2,1);
	main_grid.attach(sector_button_5,5,2,1);
	main_grid.attach(sector_button_6,6,2,1);
	main_grid.attach(sector_button_7,7,2,1);
	main_grid.attach(sector_button_8,8,2,1);
	main_grid.attach(sector_button_9,9,2,1);
	main_grid.attach(scroller,0,3,2);
	scroller.set_size_request(200,500);
	scroller.show();
	scroller.add(hex_viewer);
	
	auto context = hex_viewer.get_pango_context(); 
	auto font = context->get_font_description();
	font.set_family("Monospace");
	context->set_font_description(font);
	
	main_grid.attach(file_path_view,0,0,9);
	main_grid.attach(open_file_button,9,0,1);
	file_path_view.show();
	open_file_button.show();
	open_file_button.set_label("Open");
	open_file_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::open_file));
	
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
	error_label.show();
	reset_button.show();
	main_grid.show();
}

MainWindow::~MainWindow()
{
	fclose(image);
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
		if(button == 3) { threeSector = true;}
		targetLocationLevel5 = button;
	} else if(levelsOfView == 6) {
		hex_viewer.set_text(getHex(33000*targetLocationLevel1 +
			3300*targetLocationLevel2 +
			330*targetLocationLevel3 +
			33*targetLocationLevel4 +
			10*targetLocationLevel5 +
			1 + button));
		hex_viewer.show();
		levelsOfView = 5;
	}
	updateLevel();
}

void MainWindow::updateLevel() {
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
	int numErrors = 0;
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
			numErrors++;
		}
		free(Buf);
	}
	error_label.set_text("Total errors on disc: " + std::to_string(numErrors));
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
	return std::to_string(errors) + " Error(s)\n";
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
	int indiff;
	
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
			loc = loc1 + loc2 + loc3 + loc4 + loc5 + 1;
			diff = NULL;
			break;
		default:
			loc = 0;
			diff = 33000;
			break;
	}
	
	if(level != 5) {
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
	} else {
		if(numOfSectors >= loc) {
			sector_button_0.set_label(testSectors(loc, loc) + makeString(loc, loc));
			sector_button_0.show();
		}
		if(numOfSectors >= loc+1) {
			sector_button_1.set_label(testSectors(loc+1, loc+1) + makeString(loc+1, loc+1));
			sector_button_1.show();
		} else {
			sector_button_1.hide();
		}
		if(numOfSectors >= loc+2) {
			sector_button_2.set_label(testSectors(loc+2, loc+2) + makeString(loc+2, loc+2));
			sector_button_2.show();
		} else {
			sector_button_2.hide();
		}
		if(!threeSector) {
			if(numOfSectors >= loc+3) {
				sector_button_3.set_label(testSectors(loc+3, loc+3) + makeString(loc+3, loc+3));
				sector_button_3.show();
			} else {
				sector_button_3.hide();
			}
			if(numOfSectors >= loc+4) {
				sector_button_4.set_label(testSectors(loc+4, loc+4) + makeString(loc+4, loc+4));
				sector_button_4.show();
			} else {
				sector_button_4.hide();
			}
			if(numOfSectors >= loc+5) {
				sector_button_5.set_label(testSectors(loc+5, loc+5) + makeString(loc+5, loc+5));
				sector_button_5.show();
			} else {
				sector_button_5.hide();
			}
			if(numOfSectors >= loc+6) {
				sector_button_6.set_label(testSectors(loc+6, loc+6) + makeString(loc+6, loc+6));
				sector_button_6.show();
			} else {
				sector_button_6.hide();
			}
			if(numOfSectors >= loc+7) {
				sector_button_7.set_label(testSectors(loc+7, loc+7) + makeString(loc+7, loc+7));
				sector_button_7.show();
			} else {
				sector_button_7.hide();
			}
			if(numOfSectors >= loc+8) {
				sector_button_8.set_label(testSectors(loc+8, loc+8) + makeString(loc+8, loc+8));
				sector_button_8.show();
			} else {
				sector_button_8.hide();
			}
			if(numOfSectors >= loc+9) {
				sector_button_9.set_label(testSectors(loc+9, loc+9) + makeString(loc+9, loc+9));
				sector_button_9.show();
			} else {
				sector_button_9.hide();
			}
		} else {
			sector_button_3.hide();
			sector_button_4.hide();
			sector_button_5.hide();
			sector_button_6.hide();
			sector_button_7.hide();
			sector_button_8.hide();
			sector_button_9.hide();
		}
	}
	if(level == 4) {
		sector_button_3.set_label(testSectors(loc+(3*diff)+1, loc+(3*diff)+3) + makeString(loc+(3*diff)+1, loc+(3*diff)+3));
		sector_button_4.hide();
		sector_button_5.hide();
		sector_button_6.hide();
		sector_button_7.hide();
		sector_button_8.hide();
		sector_button_9.hide();
	}
}

void MainWindow::reset_vis() {
	levelsOfView = 0;
	targetLocationLevel1 = 0;
	targetLocationLevel2 = 0;
	targetLocationLevel3 = 0;
	targetLocationLevel4 = 0;
	targetLocationLevel5 = 0;
	updateLevel();
}

std::string MainWindow::getHex(int sector) {
	uint8_t * Buf = (uint8_t*)malloc(sizeof(uint8_t)*2352);
	fseek(image, sector*2352, SEEK_SET);
	fread(Buf, 1, 2352, image);
	std::string returnString;
	for(int i = 0; i < 2352; i=i+8) {
		std::stringstream stream;
		stream << std::hex << i << " " << std::hex << (int)Buf[i] << std::hex << (int)Buf[i+1] << " " << std::hex << (int)Buf[i+2] << std::hex << (int)Buf[i+3] << " " << std::hex << (int)Buf[i+4] << std::hex << (int)Buf[i+5] << " " << std::hex << (int)Buf[i+6] << std::hex << (int)Buf[i+7] << '\n';
		returnString = returnString + stream.str();
	}
	free(Buf);
	return returnString;
}

void MainWindow::open_file() {
	Gtk::TextBuffer::iterator start, end;
	auto buffer = file_path_view.get_buffer();
	const char *text;
	buffer->get_bounds(start, end);
	text = (char*)(buffer->get_text(start, end, FALSE)).c_str();
	image = fopen(text, "rb+");
	createSectorArray(image);
	updateLevel();
}
