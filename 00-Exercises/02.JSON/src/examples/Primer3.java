package examples;

import java.io.File;
import java.io.IOException;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ObjectNode;

public class Primer3 {

	public static void main(String[] args) throws Exception, Exception {
		
		
		ObjectMapper m = new ObjectMapper();
		AuthorsBook authorsBook = new AuthorsBook();
		
		JsonNode rootNode = m.readTree(new File("src/files/Book.json"));
		
		authorsBook.setBookTitle(rootNode.path("Title").textValue());
		
		System.out.println(rootNode.toString());
		
		
		JsonNode nameNode = rootNode.path("Author");
		authorsBook.setFirstName(nameNode.path("First_Name").textValue());
		authorsBook.setLastName(nameNode.path("Last_Name").textValue());
		
		System.out.println(authorsBook.toString());
		
		((ObjectNode)rootNode).put("Title", "ChangedTitle");
		m.writeValue(new File("src/files/Book2"), rootNode);
	
		
		System.out.println("Done!");
		
	}

}
