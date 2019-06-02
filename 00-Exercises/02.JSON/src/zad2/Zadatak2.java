package zad2;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import com.fasterxml.jackson.core.JsonEncoding;
import com.fasterxml.jackson.core.JsonFactory;
import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.databind.ObjectMapper;

import au.com.bytecode.opencsv.CSVReader;
import au.com.bytecode.opencsv.bean.ColumnPositionMappingStrategy;
import au.com.bytecode.opencsv.bean.CsvToBean;



public class Zadatak2 {

	@SuppressWarnings({ "unchecked", "rawtypes" })
	public static void main(String[] args) throws Exception {
		
		String file = "src/files/counties_cities.csv";
		CSVReader csvReader = new CSVReader(new FileReader(file), ',', '"', '\'', 1);
		
		ColumnPositionMappingStrategy strat = new ColumnPositionMappingStrategy();
		strat.setType(Country.class);
		
		
		String [] columns = new String[] {"CountryName","CapitalName","CapitalLatitude","CapitalLongitude","CountryCode","ContinentName"};
		strat.setColumnMapping(columns);
		
		
		CsvToBean csvToBean = new CsvToBean();
		
		List<Country> countries = csvToBean.parse(strat, csvReader);
		
		//Collections.sort(countries);
		
		List<Country> africa = new ArrayList();
		List<Country> asia = new ArrayList();
		List<Country> antarctica = new ArrayList();
		List<Country> australia = new ArrayList();
		List<Country> europe = new ArrayList();
		List<Country> northAmerica = new ArrayList();
		List<Country> southAmerica = new ArrayList();
		
		
		for(Country c: countries) {
			if(c.getContinentName().equalsIgnoreCase("Africa")) {
				africa.add(c);
			}else if(c.getContinentName().equalsIgnoreCase("Asia")) {
				asia.add(c);
			}else if(c.getContinentName().equalsIgnoreCase("Antarctica")) {
				antarctica.add(c);
			}else if(c.getContinentName().equalsIgnoreCase("Australia")) {
				australia.add(c);
			}else if(c.getContinentName().equalsIgnoreCase("Europe")) {
				europe.add(c);
			}else if(c.getContinentName().equalsIgnoreCase("North America")) {
				northAmerica.add(c);
			}else if(c.getContinentName().equalsIgnoreCase("South America")) {
				southAmerica.add(c);
			}
	
		}
		
		generateJSON(africa, "africa");
		generateJSON(asia, "asia");
		generateJSON(antarctica, "antarctica");
		generateJSON(australia, "australia");
		generateJSON(europe, "europe");
		generateJSON(northAmerica, "northAmerica");
		generateJSON(southAmerica, "southAmerica");
		
		
		System.out.println("Done!");
		
	}
	
	private static void generateJSON(List<Country> countries, String fileName) throws IOException {
		
		ObjectMapper mapper = new ObjectMapper();
		mapper.writeValue(new File("src/files/" + fileName + ".json"), countries);
		
	}

}
