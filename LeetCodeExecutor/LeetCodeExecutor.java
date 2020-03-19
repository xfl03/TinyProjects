import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

public class LeetCodeExecutor {
    static Method method = null;
    static Object solution = null;

    public static void main(String... args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String str;
        while (!"".equals(str = br.readLine())) {
            System.out.println(invoke(str));
        }
    }

    static String invoke(String str) {
        Data data = toData(str);
        if (method == null) {
            initMethod(data);
        }
        if (method == null) {
            System.err.println(String.format("No method found for '%s'.", data.toTypeString()));
            return null;
        }
        return data.invoke(method, solution);
    }

    static void initMethod(Data data) {
        try {
            Class<?> clazz = Class.forName("Solution");
            solution = clazz.newInstance();
            Method[] methods = clazz.getMethods();
            for (Method m : methods) {
                if (data.canAccept(m)) {
                    method = m;
                }
            }
        } catch (ClassNotFoundException e) {
            System.err.println("Class 'Solution' not found.");
        } catch (IllegalAccessException | InstantiationException e) {
            System.err.println("Class 'Solution' doesn't have default constructor.");
        }
    }

    enum Status {
        WAITING,
        WAITING_VALUE,
        READING_INT,
        READING_STRING,
        WAITING_ARRAY,
        READING_INT_ARRAY,
        READING_STRING_ARRAY
    }

    static Data toData(String s) {
        Data data = new Data();
        Status status = Status.WAITING;

        StringBuilder buffer = new StringBuilder();
        List<Object> listBuffer = new ArrayList<>();
        Object[] typeBuffer = new Object[0];
        for (char c : s.toCharArray()) {
            switch (status) {
                case WAITING:
                    if (c == '"') {
                        status = Status.READING_STRING;
                        buffer = new StringBuilder();
                    } else if (c == '[') {
                        status = Status.WAITING_ARRAY;
                        listBuffer.clear();
                    } else if (c == '-' || isNum(c)) {
                        status = Status.READING_INT;
                        buffer = new StringBuilder();
                        buffer.append(c);
                    } else if (isLetter(c)) {
                        status = Status.WAITING_VALUE;
                    }
                    break;
                case WAITING_VALUE:
                    if (c == '=') {
                        status = Status.WAITING;
                    }
                    break;
                case READING_INT:
                    if (isNum(c)) {
                        buffer.append(c);
                    } else {
                        data.add(Integer.parseInt(buffer.toString()));
                        status = Status.WAITING;
                    }
                    break;
                case READING_STRING:
                    if (c == '"') {
                        data.add(buffer.toString());
                        status = Status.WAITING;
                    } else {
                        buffer.append(c);
                    }
                    break;
                case WAITING_ARRAY:
                    if (c == '"') {
                        status = Status.READING_STRING_ARRAY;
                        buffer = new StringBuilder();
                        typeBuffer = new String[0];
                    } else if (c == ']') {
                        data.add(listBuffer.toArray(typeBuffer));
                        status = Status.WAITING;
                    } else if (c == '-' || isNum(c)) {
                        status = Status.READING_INT_ARRAY;
                        buffer = new StringBuilder();
                        buffer.append(c);
                        typeBuffer = new Integer[0];
                    }
                    break;
                case READING_INT_ARRAY:
                    if (isNum(c)) {
                        buffer.append(c);
                    } else {
                        listBuffer.add(Integer.parseInt(buffer.toString()));
                        if (c == ']') {
                            data.add(listBuffer.toArray(typeBuffer));
                            status = Status.WAITING;
                        } else {
                            status = Status.WAITING_ARRAY;
                        }
                    }
                    break;
                case READING_STRING_ARRAY:
                    if (c == '"') {
                        listBuffer.add(buffer.toString());
                        status = Status.WAITING_ARRAY;
                    } else {
                        buffer.append(c);
                    }
                    break;
            }
        }
        if (status == Status.READING_INT) {
            data.add(Integer.parseInt(buffer.toString()));
        }
        return data;
    }

    static boolean isNum(char c) {
        return c >= '0' && c <= '9';
    }

    static boolean isLetter(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

}

class Data {
    List<Object> objects;

    public Data() {
        objects = new ArrayList<>();
    }

    public void add(Object o) {
        objects.add(o);
    }

    public boolean canAccept(Method method) {
        if (method.getParameterCount() != objects.size()) {
            return false;
        }
        Class<?>[] args = method.getParameterTypes();
        for (int i = 0; i < args.length; ++i) {
            if (!isSameType(objects.get(i).getClass(), args[i])) {
                return false;
            }
        }
        return true;
    }

    private boolean isSameType(Class<?> o, Class<?> c) {
        if (o == Integer.class && c == int.class) {
            return true;
        }
        if (o == Integer[].class && c == int[].class) {
            return true;
        }
        return o == c;
    }

    public String invoke(Method method, Object instance) {
        Object[] objs = objects.toArray();
        try {
            return method.invoke(instance, objs).toString();
        } catch (InvocationTargetException | IllegalAccessException e) {
            e.printStackTrace();
        }
        return null;
    }

    public String toString() {
        StringBuilder builder = new StringBuilder("[");
        for (int i = 0; i < objects.size(); i++) {
            builder.append(objects.get(i).toString());
            if (i != objects.size() - 1) {
                builder.append(", ");
            }
        }
        builder.append("]");
        return builder.toString();
    }

    public String toTypeString() {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < objects.size(); i++) {
            builder.append(objects.get(i).getClass().getTypeName());
        }
        return builder.toString();
    }
}
