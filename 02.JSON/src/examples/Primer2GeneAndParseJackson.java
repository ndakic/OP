package examples;

import java.io.File;
import java.io.IOException;

import com.fasterxml.jackson.core.JsonEncoding;
import com.fasterxml.jackson.core.JsonFactory;
import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.core.JsonParser;
import com.fasterxml.jackson.core.JsonToken;

public class Primer2GeneAndParseJackson {

	public static void main(String[] args) throws Exception {
		
		
		AuthorsBook a = new AuthorsBook();
		
		generateJSON();
		parseJSON(a, "src/files/Book_generated.json");
		System.out.println(a.toString());
		
		parseJSON(a, "src/files/Book.json");
		System.out.println(a.toString());
		
		System.out.println("Done!");
		
	}
	
	
	private static void parseJSON(AuthorsBook authorsBook, String bookName) throws Exception, Exception {
		
		JsonFactory f = new JsonFactory();
		JsonParser jp = f.createParser(new File(bookName));
		
		jp.nextToken();
		
		while(jp.nextToken() != JsonToken.END_OBJECT) {
			String fieldName = jp.getCurrentName();
			jp.nextToken();
			if("Author".equals(fieldName)) {
				while(jp.nextToken() != JsonToken.END_OBJECT) {
					String nameField = jp.getCurrentName();
					jp.nextToken();
					if("First_Name".equals(nameField)) {
						authorsBook.setFirstName(jp.getText());
					}else if ("Last_Name".equals(nameField)) {
						authorsBook.setLastName(jp.getText());
					}
				}
			}else if("Title".equals(fieldName)) {
				authorsBook.setBookTitle(jp.getText());
			}else {
				System.out.println("Error!");
			}
			
		}
		
		
		jp.close();
		
	}
	
	private static void generateJSON() throws Exception {
		

		JsonFactory f = new JsonFactory();
		JsonGenerator g = f.createGenerator(new File("src/files/Book_generated.json"), JsonEncoding.UTF8);
		
		g.writeStartObject();
		
		g.writeObjectFieldStart("Author");
		g.writeStringField("First_Name", "Stephen");
		g.writeStringField("Last_Name", "King");
		g.writeEndObject();
		
		g.writeStringField("Title", "The Green Mile");
		g.writeEndObject();
		
		g.close();
	}

}
