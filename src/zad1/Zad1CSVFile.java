package zad1;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import au.com.bytecode.opencsv.CSVReader;
import au.com.bytecode.opencsv.CSVWriter;
import au.com.bytecode.opencsv.bean.ColumnPositionMappingStrategy;
import au.com.bytecode.opencsv.bean.CsvToBean;

public class Zad1CSVFile {

	public static void main(String[] args) throws Exception {
		
		String file = "src/files/points.csv";
		CSVReader csvReader = new CSVReader(new FileReader(file),',','\'', 1);
		
		
		ColumnPositionMappingStrategy strat = new ColumnPositionMappingStrategy();
		strat.setType(Point.class);
		
		
		String [] columns = new String[] {"x", "y", "z"};
		strat.setColumnMapping(columns);
		
		
		CsvToBean csvToBean = new CsvToBean();
		
		List<Object> list = csvToBean.parse(strat, csvReader);
		List<Point> points = new ArrayList();
		
		// racunanje p i pravljenje liste kordinata
		for(Object obj: list) {
			Point kord = (Point) obj;
			Integer calculateP = Integer.parseInt(kord.getX())  + Integer.parseInt(kord.getY()) + Integer.parseInt(kord.getZ());
			kord.setP(calculateP.toString());
			points.add(new Point(kord.getX(), kord.getY(), kord.getZ(), kord.getP()));
		}
		
		// sortiranje kordinata
		Collections.sort(points);
		
		
		// pravljenje redova za cuvanje u datoteku
		List<String[]> redovi = new ArrayList();
		
		for(Point kor: points) {
			String [] red = new String [] {kor.getX(), kor.getY(), kor.getZ(), kor.getP()};
			redovi.add(red);
		}
		
		String outputFile = "src/files/pointsOutput.csv";
		CSVWriter csvWriter = new CSVWriter(new FileWriter(outputFile), '#', CSVWriter.NO_QUOTE_CHARACTER);
		csvWriter.writeAll(redovi); // cuvanje
		
		// krajnji rezultat
		for(Point kor: points)
			System.out.println(kor.toString());
		
		
		System.out.println("Done!");
		
		csvReader.close();
		csvWriter.close();

	}

}
