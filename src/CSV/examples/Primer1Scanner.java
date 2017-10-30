package CSV.examples;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Primer1Scanner {

	public static void main(String[] args) throws Exception {
		
		
		Scanner scanner = new Scanner(new File("src/CSV/files/drzave_gradovi.csv"));

		scanner.useDelimiter(",");

		while (scanner.hasNext()) {
			System.out.print(scanner.next() + "|");
		}

		scanner.close();
		

	}

}
