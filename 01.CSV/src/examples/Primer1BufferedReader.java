package examples;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Primer1BufferedReader {

	public static void main(String[] args) {
		
		
		String csvFilename = "src/files/drzave_gradovi.csv";
		BufferedReader fileReader = null;
		
		final String DELIMITER = ",";
		try
			{
			String line = "";
			fileReader = new BufferedReader(new FileReader(csvFilename));
			while ((line = fileReader.readLine()) != null) {
				String[] tokens = line.split(DELIMITER);
				for(String token : tokens)
				{
					System.out.print(token + "|");
				}
					System.out.println("");
			}
		} catch (Exception e) {
				e.printStackTrace();
		}
		
		finally{
			try {
				fileReader.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		

	}

}
