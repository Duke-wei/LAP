package TestReadXML;

import ReadXML.XmlByDom;
import ReadXML.XmlByDom4j;
import ReadXML.XmlBySAX;

public class test{
    public static void main(String[] args){
//        Readxml rx = new Readxml("Resources/test2.xml");
//        rx.testRead();
//        String t = "asdfasdfasdfasdf";
//        System.out.println(t.substring(0,t.length()>1200?1200:t.length()));
        //test XmlByDom
//        XmlByDom domdemo = new XmlByDom();
//        domdemo.parserXml("src/test/resources/test.xml");
        //test XmlBySAX
//        XmlBySAX saxdemo = new XmlBySAX();
//        saxdemo.parserXml("src/test/resources/test.xml");
        //test XmlByDom4j
        XmlByDom4j dom4jdemo = new XmlByDom4j();
        dom4jdemo.parserXml("src/test/resources/test2.xml");
    }
}