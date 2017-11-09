package zad1;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import com.fasterxml.jackson.databind.ObjectMapper;

import au.com.bytecode.opencsv.CSVWriter;
import au.com.bytecode.opencsv.bean.BeanToCsv;
import au.com.bytecode.opencsv.bean.ColumnPositionMappingStrategy;

public class Zadatak1 {

	@SuppressWarnings("unused")
	public static void main(String[] args) throws Exception {
		
		List<Podatak> podaci = createCSV("podaci");
		
		saveDataToJson(podaci, "podaci");

	}
	
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public static List<Podatak> createCSV(String fileName) throws IOException {
		
		Podatak podatak1 = new Podatak("1", "Novi Sad", "Beograd", "01.01.2017.", "11:00", "12:00", "1", 500, 10, 0);
		Podatak podatak2 = new Podatak("2", "Novi Sad", "Subotica", "11.01.2017.", "14:00", "16:00", "4", 700, 10, 0);
		Podatak podatak3 = new Podatak("3", "Novi Sad", "Uzice", "12.01.2017.", "16:00", "18:00", "6", 200, 4, 0);
		Podatak podatak4 = new Podatak("4", "Novi Sad", "Valjevo", "04.01.2017.", "18:00", "19:00", "5", 650, 3, 0);
		Podatak podatak5 = new Podatak("5", "Novi Sad", "Vranje", "16.01.2017.", "16:00", "17:00", "4", 500, 18, 0);
		Podatak podatak6 = new Podatak("6", "Novi Sad", "Zrenjenin", "16.01.2017.", "16:00", "17:00", "3", 500, 18, 0);
		Podatak podatak7 = new Podatak("7", "Novi Sad", "Sombor", "16.01.2017.", "16:00", "17:00", "5", 500, 18, 0);
		Podatak podatak8 = new Podatak("8", "Novi Sad", "Nis", "16.01.2017.", "16:00", "18:00", "3", 500, 18, 0);
		Podatak podatak9 = new Podatak("9", "Novi Sad", "Becej", "16.01.2017.", "16:00", "19:00", "3", 500, 18, 0);
		Podatak podatak10 = new Podatak("10", "Novi Sad", "Beograd", "16.01.2017.", "16:00", "20:00", "4", 500, 18, 0);
		Podatak podatak11 = new Podatak("1", "Novi Sad", "Beograd", "01.01.2017.", "15:00", "19:00", "2", 510, 10, 0);
		Podatak podatak12 = new Podatak("1", "Novi Sad", "Beograd", "01.01.2017.", "15:00", "17:00", "1", 550, 10, 0);
		Podatak podatak13 = new Podatak("6", "Novi Sad", "Zrenjenin", "16.01.2017.", "17:00", "20:00", "3", 500, 8, 0);
		Podatak podatak14 = new Podatak("6", "Novi Sad", "Zrenjenin", "16.01.2017.", "17:30", "23:00", "4", 500, 9, 0);
		Podatak podatak15 = new Podatak("6", "Novi Sad", "Zrenjenin", "16.01.2017.", "19:00", "22:00", "6", 540, 8, 0);
		Podatak podatak16 = new Podatak("6", "Novi Sad", "Zrenjenin", "16.01.2017.", "20:00", "21:00", "3", 590, 19, 0);
		
		List<Podatak> podaci = new ArrayList();
		
		podaci.add(podatak1);
		podaci.add(podatak2);
		podaci.add(podatak3);
		podaci.add(podatak4);
		podaci.add(podatak5);
		podaci.add(podatak6);
		podaci.add(podatak7);
		podaci.add(podatak8);
		podaci.add(podatak9);
		podaci.add(podatak10);
		podaci.add(podatak11);
		podaci.add(podatak12);
		podaci.add(podatak13);
		podaci.add(podatak14);
		podaci.add(podatak15);
		podaci.add(podatak16);
		
		CSVWriter csvWriter = new CSVWriter(new FileWriter("src/files/" + fileName +".csv"), ',', CSVWriter.NO_QUOTE_CHARACTER);
			
		ColumnPositionMappingStrategy strat = new ColumnPositionMappingStrategy();
		strat.setType(Podatak.class);
		
		
		String [] columns = new String[] {"sifraRelacije", "mestoPolaska", "mestoDolaska",  
				"datumPolaska", "vremePolaska", "planiranoVremeDolaska", "peronPolaska", "cenaKarte", "brProdKarata", "brRelacija"};
		strat.setColumnMapping(columns);
				
		
		BeanToCsv bc = new BeanToCsv();
		bc.write(strat,csvWriter, podaci);
		
		csvWriter.close();
		
		return podaci;
		
		
	}
	
	@SuppressWarnings("unchecked")
	public static void saveDataToJson(List<Podatak> podaci, String fileName) throws Exception {
		
		List<Relacija> relacije = new ArrayList<>();
		List<Polazak> polasci = new ArrayList<>();
		
		for(Podatak podatak: podaci) {
			
			Relacija relacija = new Relacija(podatak.getSifraRelacije(), podatak.getMestoPolaska(), podatak.getMestoDolaska());
			
			Polazak polazak = new Polazak(podatak.getSifraRelacije(), podatak.getDatumPolaska(), podatak.getVremePolaska(), 
					podatak.getPlaniranoVremeDolaska(), podatak.getPeronPolaska(), podatak.getCenaKarte(), podatak.getBrProdKarata());
			
			
			relacije.add(relacija);
			polasci.add(polazak);
			
		}
		
		RelacijaPolazak relacijaPolasci = new RelacijaPolazak(relacije, polasci);
			
		ObjectMapper mapper = new ObjectMapper();
		
		mapper.writeValue(new File("src/files/" + fileName + ".json"), relacijaPolasci);
		
	}

}

