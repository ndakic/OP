package examples;

import java.io.File;
import java.io.IOException;

import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

public class Primer1JSONMapper {

	public static void main(String[] args) throws Exception, JsonMappingException, Exception {
		
		ObjectMapper mapper = new ObjectMapper();
		
		Book book = mapper.readValue(new File("src/files/Book.json"), Book.class);
		
		System.out.println(book.toString());

	}

}
