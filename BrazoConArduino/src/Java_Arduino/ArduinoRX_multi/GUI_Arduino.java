
package Java_Arduino.ArduinoRX_multi;

/**
 * * @author Beltran Rico Daniela
 *    Sistemas Programables
 */

import java.awt.BorderLayout;
import java.util.ArrayList;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.table.DefaultTableModel;
import com.panamahitek.ArduinoException;
import com.panamahitek.PanamaHitek_Arduino;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.logging.Level;
import java.util.logging.Logger;
import jssc.SerialPortException;

public class GUI_Arduino extends JFrame {
    int num, resultado;
    String ayuda;
    JButton btnAbortar,btnTapa,btnAgregar;
    JTextField txtPinza,tstHombro,txtCodo,txtPasos;
    JLabel lblAgregarSecuencia,lblPinza,lblHombro,lblCodo,lblPasos;
    
    PanamaHitek_Arduino ino = new PanamaHitek_Arduino();
    String msg1,msg2,msg3,msg4,msg;


    public GUI_Arduino() {
        
        super("Brazo robotico");

        setLocationRelativeTo(null);
        setLayout(new FlowLayout());
        txtPinza = new JTextField(15);
        tstHombro = new JTextField(15);
        txtCodo = new JTextField(15);
        txtPasos = new JTextField(15);
        lblAgregarSecuencia = new JLabel("Agregar secuencia");
        lblPinza= new JLabel("Pinza: ");
        lblHombro= new JLabel("Hombro: ");
        lblCodo= new JLabel("Codo: ");
        lblPasos= new JLabel("Pasos: ");
        btnAbortar = new JButton("Abortar");
        btnAgregar = new JButton("Cargar secuencia");
        add(lblPinza);
        add(txtPinza);
        
        add(lblHombro);
        add(tstHombro);
        
        add(lblCodo);
        add(txtCodo);
        
        add(lblPasos);
        add(txtPasos);
        add(btnAbortar);
        add(btnAgregar);
        
        try {
            //Se inicia la comunicación con el Puerto Serie
            ino.arduinoTX("COM3", 9600);
        } catch (ArduinoException ex) {
            Logger.getLogger(GUI_Arduino.class.getName()).log(Level.SEVERE, null, ex);
        }

        btnAgregar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                
                String texto1= txtPinza.getText();
                txtPinza.setText("");
                String texto2= tstHombro.getText();
                tstHombro.setText("");
                String texto3= txtCodo.getText();
                txtCodo.setText("");
                String texto4= txtPasos.getText();
                txtPasos.setText("");
                
                
                msg1=texto1;
                msg2=texto2;
                msg3=texto3;
                msg4=texto4;
                
                msg=texto1+","+texto2+","+texto3+","+texto4+".";
                
                try {
                     ino.sendData(""+msg);
                     JOptionPane.showMessageDialog(null, "Secuencia realizada: "+msg);
                } catch (ArduinoException | SerialPortException ex) {
                    Logger.getLogger(GUI_Arduino.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
        
        btnAbortar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });
    }
    
    
     public static void main(String[] args) {
        GUI_Arduino objFact=new GUI_Arduino();
        objFact.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        objFact.setSize(200,300);
        objFact.setVisible(true);
        objFact.setResizable(false);
        
    }
}
