package examples;

import java.io.FileNotFoundException;
import java.io.FileReader;

import au.com.bytecode.opencsv.CSVReader;

public class Primer1CSVReader {

	public static void main(String[] args) throws Exception {
		
		String csvFilename = "src/files/drzave_gradovi.csv";
		CSVReader csvReader = new CSVReader(new FileReader(csvFilename));
		String[] row = null;

		while((row = csvReader.readNext()) != null) {
			String rowData = "";

			for(int i = 0; i < row.length; i++){
				rowData += row[i];

				if(i != row.length - 1)
					rowData += ",";
			}

			System.out.println(rowData);
		}

		csvReader.close();

	}

}
