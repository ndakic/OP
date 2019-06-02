package zadaci;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.yaml.snakeyaml.DumperOptions;
import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;
import org.yaml.snakeyaml.constructor.SafeConstructor;
import org.yaml.snakeyaml.introspector.Property;
import org.yaml.snakeyaml.nodes.NodeTuple;
import org.yaml.snakeyaml.nodes.Tag;
import org.yaml.snakeyaml.representer.Representer;

import com.fasterxml.jackson.databind.ObjectMapper;

public class Zadatak4 {

	@SuppressWarnings({ "unused", "rawtypes", "unchecked" })
	public static void main(String[] args) throws Exception {
		
		ObjectMapper mapper = new ObjectMapper();
		
	    InputStream input = new FileInputStream(new File("src/files/log.yaml"));
	    Yaml yaml = new Yaml();
	    
	    List<Log> logs = new ArrayList();

	    for (Object data : yaml.loadAll(input)) {
	        Log log = mapper.convertValue(data, Log.class);
	        logs.add(log);
	    }
	    
	    String warn = "src/files/log_warn.yaml";
	    String error = "src/files/log_error.yaml";
	    List<Log> warns = new ArrayList();
	    List<Log> errors = new ArrayList();
	    
	    DumperOptions opts = new DumperOptions();
		opts.setDefaultFlowStyle(DumperOptions.FlowStyle.BLOCK);
	
		Yaml yamlw = new Yaml(representer, opts);
		
	    for(Log log: logs) {
	    	if(log.getWarning() != null) {
	    		warns.add(log);
	    	}
	    	if(log.getStack() != null || log.getFatal() != null) {
	    		errors.add(log);		
	    	}
	    	System.out.println(log.toString());
	    }
	    
	    yamlw.dump(warns, new FileWriter(new File(warn)));
	    yamlw.dump(errors, new FileWriter(new File(error)));
	    
	    System.out.println("Done!");
		
	}
	
	static Representer representer = new Representer() {
	    @Override
	    protected NodeTuple representJavaBeanProperty(Object javaBean, Property property, Object propertyValue,Tag customTag) {
	        // if value of property is null, ignore it.
	        if (propertyValue == null) {
	            return null;
	        }  
	        else {
	            return super.representJavaBeanProperty(javaBean, property, propertyValue, customTag);
	        }
	    }
	};

}
