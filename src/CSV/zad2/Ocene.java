package CSV.zad2;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import au.com.bytecode.opencsv.CSVReader;
import au.com.bytecode.opencsv.CSVWriter;
import au.com.bytecode.opencsv.bean.ColumnPositionMappingStrategy;
import au.com.bytecode.opencsv.bean.CsvToBean;

public class Ocene {

	public static void main(String[] args) throws Exception {
		
		String filePath = "src/CSV/files/studenti.csv";
		CSVReader csvReader = new CSVReader(new FileReader(filePath), ',', '\'', 1);
		
		ColumnPositionMappingStrategy strat = new ColumnPositionMappingStrategy();
		strat.setType(Student.class);
		
		String [] zaglavlje = new String [] {"index", "ime", "predmet", "ocena"};
		strat.setColumnMapping(zaglavlje);
		
		CsvToBean csvToBean = new CsvToBean();
		
		List<Student> studenti = csvToBean.parse(strat, csvReader);
		
		HashMap<String, String> petice = new HashMap();
		HashMap<String, String> sestice = new HashMap();
		HashMap<String, String> sedmice = new HashMap();
		HashMap<String, String> osmice  = new HashMap();
		HashMap<String, String> devetke = new HashMap();
		HashMap<String, String> desetke = new HashMap();
		
		
		for(Student st: studenti) {
			
			int ukupno5 = count(studenti, st.getIndex(), 5);
			petice.put(st.getIndex(), Integer.toString(ukupno5));
			
			int ukupno6 = count(studenti, st.getIndex(), 6);
			sestice.put(st.getIndex(), Integer.toString(ukupno6));
			
			int ukupno7 = count(studenti, st.getIndex(), 7);
			sedmice.put(st.getIndex(), Integer.toString(ukupno7));
			
			int ukupno8 = count(studenti, st.getIndex(), 8);
			osmice.put(st.getIndex(), Integer.toString(ukupno8));
			
			int ukupno9 = count(studenti, st.getIndex(), 9);
			devetke.put(st.getIndex(), Integer.toString(ukupno9));
			
			int ukupno10 = count(studenti, st.getIndex(), 10);
			desetke.put(st.getIndex(), Integer.toString(ukupno10));
			
		}
		
		List<String []> pet = makeList(petice, studenti);
		List<String []> sest = makeList(sestice, studenti);
		List<String []> sedam = makeList(sedmice, studenti);
		List<String []> osam = makeList(osmice, studenti);
		List<String []> devet = makeList(devetke, studenti);
		List<String []> deset = makeList(desetke, studenti);
		
		saveData(pet, "petice");
		saveData(sest, "sestice");
		saveData(sedam, "sedmice");
		saveData(osam, "osmice");
		saveData(devet, "devetke");
		saveData(deset, "desetke");
		
		List<String []> polozenoIprosek = new ArrayList();
		
		for(Student stude: studenti) {
			 String [] st = polIprosek(studenti, stude.getIndex());
			 
			 if(checkList(polozenoIprosek, stude.getIndex()) == -1) {
				 polozenoIprosek.add(st);
			 }
			 
		}
		
		saveData(polozenoIprosek, "polIprosek");
		
		csvReader.close();
		System.out.println("Done!");

	}
	
public static void saveData(List<String []> data, String fileName) throws Exception {
		
		String file = "src/CSV/files/"+ fileName + ".csv";
		CSVWriter csvWriter = new CSVWriter(new FileWriter(file), ',', CSVWriter.NO_QUOTE_CHARACTER);
		
		csvWriter.writeAll(data);
		
		csvWriter.close();
		
	}
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public static List<String []> makeList(HashMap<String, String> HashMapa, List<Student> studenti){
		
		List<String []> lista = new ArrayList();
		
		for (Map.Entry<String, String> entry : HashMapa.entrySet()) {
		    
		    String [] student = getStudentIndexAndName(studenti, entry.getKey());
		    String [] fullStudent = new String [] {student[0], student[1], entry.getValue()};
		    
		    lista.add(fullStudent);
		    
		}
		
		return lista;
		
	}
	
	public static String [] getStudentIndexAndName(List<Student> studenti, String index) {
		
		String [] student = null;
		
		for(Student stud: studenti) {
			if(stud.getIndex().equalsIgnoreCase(index)) {
				student = new String [] {stud.getIndex(), stud.getIme()};
				break;
			}
		}
		
		return student;
		
	}
	
 	public static int count(List<Student> lista, String index, int ocena) {
		
		int brojac = 0;
		
		for(Student student: lista) {
			
			if(Integer.parseInt(student.getOcena()) == ocena) {
				
				if(student.getIndex().equalsIgnoreCase(index)) {
					brojac += 1;
				}
				
			}
			

		}
		
		return brojac;
	}
 	
 	public static String [] polIprosek(List<Student> lista, String index) {
 		
 		double brojPolozenih = 0;
 		double zbirOcena = 0;
 		
 		for(Student student: lista) {
 			if(Integer.parseInt(student.getOcena()) != 5 && student.getIndex().equalsIgnoreCase(index)) {
 				brojPolozenih += 1;
 				zbirOcena += Integer.parseInt(student.getOcena());
 			}
 		}
 		

 		double prosek = zbirOcena / brojPolozenih;
 		
 		Student stud = getStudent(lista, index);
 		
 		String [] student = new String [] {stud.getIndex(), stud.getIme(), Double.toString(brojPolozenih), Double.toString(prosek)};
 		
 		return student;
 		
 	}
 	
 	public static Student getStudent(List<Student> lista, String index) {
 		
 		Student student = null;
 		
 		for(Student stud: lista) {
 			if(stud.getIndex().equalsIgnoreCase(index)) {
 				student = stud;
 				break;
 			}
 		}
 		
 		return student;
 		
 	}
 	
 	public static int checkList(List<String []> polozenoIprosek, String index) {
 		
 		int status = -1;
 		
 		for(int i = 0; i < polozenoIprosek.size(); i++) {
 			if(polozenoIprosek.get(i)[0].equalsIgnoreCase(index)) {
 				status = 1;
 			}
 		}
 		return status;
 	}

}
