package examples;

import java.io.FileWriter;
import java.io.IOException;

import au.com.bytecode.opencsv.CSVWriter;

public class Primer2CsvWritterNext {

	public static void main(String[] args) throws Exception {
		
		String csv = "src/files/drzave_gradovi3.csv";
		CSVWriter writer = new CSVWriter(new FileWriter(csv));

		String [] country = "Australia,Canberra".split(",");
		writer.writeNext(country);

		country = "Canada,Ottawa".split(",");
		writer.writeNext(country);

		country = "China,Beijing".split(",");
		writer.writeNext(country);

		country = "France,Paris".split(",");
		writer.writeNext(country);

		writer.close();

	}

}
