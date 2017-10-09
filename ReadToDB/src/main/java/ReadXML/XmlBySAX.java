package ReadXML;

import org.xml.sax.Attributes;
import org.xml.sax.HandlerBase;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

/**
 * Created by wengwei on 17-6-16.
 */
public class XmlBySAX implements XmlDocument{
    @Override
    public void parserXml(String FileName) {
        SAXParserFactory saxfac = SAXParserFactory.newInstance();
        try{
            SAXParser saxParser = saxfac.newSAXParser();
            InputStream is = new FileInputStream(FileName);
            saxParser.parse(is,new MySAXHandler());
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        }catch (SAXException e){
            e.printStackTrace();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private class MySAXHandler extends DefaultHandler{
        boolean hasAttribute = false;
        Attributes attributes = null;

        public void startDocument() throws SAXException{

        }

        public void endDocument() throws SAXException{

        }

        public void startElement(String uri,String localName,String qname,Attributes attributes) throws SAXException{
//            System.out.println("this is startElement qname is "+qname);
//            System.out.println("this is startElement qname:"+qname+" uri:"+uri+" localName:"+localName);
            if(qname.equals("users")){
                return;
            }
            if(qname.equals("user")){
                return;
            }
            if(attributes.getLength()>0){
                this.attributes = attributes;
                this.hasAttribute = true;
            }
        }

        public void endElement(String uri,String localName,String qName) throws SAXException{
            if(hasAttribute && (attributes!=null)){
                for(int i=0;i<attributes.getLength();++i){
                    System.out.println(attributes.getQName(i)+":"+attributes.getValue(i));
                }
            }
        }

        public void characters(char[] ch,int start,int length) throws SAXException{
//            System.out.println("this is characters start:"+start+" length:"+length);
//            System.out.println("this is characters ch[] is:"+new String(ch));
            System.out.println(new String(ch,start,length));
        }
    }
}
