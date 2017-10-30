package CSV.examples;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import au.com.bytecode.opencsv.CSVWriter;

public class Primer2CsvWritterAll {

	public static void main(String[] args) throws Exception {
		
		
		String csv = "src/CSV/files/drzave_gradovi2.csv";
		CSVWriter writer = new CSVWriter(new FileWriter(csv));

		List<String[]> data = new ArrayList<String[]>();

		data.add(new String[] {"Australia", "Canberra"});
		data.add(new String[] {"Canada", "Ottawa"});
		data.add(new String[] {"China", "Beijing"});
		data.add(new String[] {"France", "Paris"});

		writer.writeAll(data);

		writer.close();
		

	}

}
