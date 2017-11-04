package zadaci;

import java.util.Date;

public class Log {
	
	private String Time;
	private String Date;
	private String User;
	private String Warning;
	private String Fatal;
	private Stack Stack;
	
	public Log() {
		super();
	}

	public Log(String time, String date, String user, String warning, String fatal, zadaci.Stack stack) {
		super();
		Time = time;
		Date = date;
		User = user;
		Warning = warning;
		Fatal = fatal;
		Stack = stack;
	}

	public String getTime() {
		return Time;
	}

	public void setTime(String time) {
		Time = time;
	}

	public String getDate() {
		return Date;
	}

	public void setDate(String date) {
		Date = date;
	}

	public String getUser() {
		return User;
	}

	public void setUser(String user) {
		User = user;
	}

	public String getWarning() {
		return Warning;
	}

	public void setWarning(String warning) {
		Warning = warning;
	}

	public String getFatal() {
		return Fatal;
	}

	public void setFatal(String fatal) {
		Fatal = fatal;
	}

	public Stack getStack() {
		return Stack;
	}

	public void setStack(Stack stack) {
		Stack = stack;
	}

	@Override
	public String toString() {
		return "Log [Time=" + Time + ", Date=" + Date + ", User=" + User + ", Warning=" + Warning + ", Fatal=" + Fatal
				+ ", Stack=" + Stack + "]";
	}


	
}


