package examples;

import java.io.FileReader;
import java.io.IOException;
import java.util.List;

import au.com.bytecode.opencsv.CSVReader;
import au.com.bytecode.opencsv.bean.ColumnPositionMappingStrategy;
import au.com.bytecode.opencsv.bean.CsvToBean;

public class Primer3CsvToBean {

	public static void main(String[] args) throws Exception {
		/*
		Pročitati sadržaj datoteke drzave_gradovi.csv u odgovarajuću listu
		bean-ova i ispisati nazive glavnih gradova.
		*/
		
		String csvFilename = "src/files/drzave_gradovi.csv";
		CSVReader csvReader = new CSVReader(new FileReader(csvFilename));
		
		ColumnPositionMappingStrategy strat = new ColumnPositionMappingStrategy();
		strat.setType(Country.class);
		
		//column names from the bean (case insensitive)
		String[] columns = new String[] {"countryName", "capitalName", "capitalLatitude",
		"capitalLongitude", "countryCode", "continentName"};

		strat.setColumnMapping(columns);
		
		CsvToBean csv = new CsvToBean();
		
		List list = csv.parse(strat, csvReader);
		for (Object object : list) {
			Country country = (Country) object;
			System.out.println(country.getCapitalName());
		}
		
		csvReader.close();

	}

}
