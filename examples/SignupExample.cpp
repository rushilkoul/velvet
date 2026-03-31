#include <velvet/core>
#include <string>

int main() {
    Window window(800, 600, "Sign Up Form Example");

    VStack root(24);
    root.setAlignItems("center");
 
    Label title("Create your account", {
        {"fontSize", 32.f},
        {"fontStyle", "bold"}
    });

    Label subtitle("It only takes a few seconds.", {
        {"fontSize", 18.f},
        {"fillColor", 0x555555FFu}
    });

    VStack form(16);

    form.setWidth(420);

    Label nameLabel("Full name", {
        {"fontSize", 18.f}
    });

    InputField nameInput("John Doe", {
        {"fontSize", 20.f},
        {"backgroundColor", 0xFFFFFFFFu},
        {"width", 380.f}
    });

    Label emailLabel("Email address", {
        {"fontSize", 18.f}
    });

    InputField emailInput("you@example.com", {
        {"fontSize", 20.f},
        {"backgroundColor", 0xFFFFFFFFu},
        {"width", 380.f}
    });

 
    Label passwordLabel("Password", {
        {"fontSize", 18.f}
    });

    InputField passwordInput("*********", {
        {"fontSize", 20.f},
        {"backgroundColor", 0xFFFFFFFFu},
        {"width", 380.f}
    });

    HStack termsRow(8); 

    termsRow.setPadding(0, 0, 0, 8);

    Label termsPrefix("By clicking Sign up, you agree to our ", {
        {"fontSize", 14.f}
    });
    Label termsLink("Terms", {
        {"fontSize", 14.f},
        {"fontStyle", "italic"},
        {"backgroundColor", 0xFFED29FFu}
    });

    Label termsSuffix(" and Privacy Policy.", {
        {"fontSize", 14.f}
    });
    termsRow.add(termsPrefix, termsLink, termsSuffix);

    HStack buttonsRow(16);  


    buttonsRow.setPadding(8, 0, 0, 0);

    Button cancelBtn(150.f, 48.f, "Cancel", {
        {"backgroundColor", 0xE0E0E0FFu},
        {"hoverBackgroundColor", 0xCCCCCCFFu}
    });

    Button signupBtn(200.f, 48.f, "Sign up", {
        {"backgroundColor", 0x4285F4FFu}, 
        {"hoverBackgroundColor", 0x3367D6FFu},
        {"fontColor", 0xFFFFFFFFu},
        {"hoverFontColor", 0xFFFFFFFFu}
    }); 


    Label pad("");
    
    Label status("", {
        {"fontSize", 16.f}
    });

    buttonsRow.add(cancelBtn, signupBtn);

    cancelBtn.onclick = [&] {
        window.close();
    };

    signupBtn.onclick = [&] {
        status.setText("Thanks, " + std::string("user") +  "! Your account has been created."); 
    };

    form.add(
        nameLabel,
        nameInput,
        emailLabel, 
        emailInput,
        passwordLabel,
        passwordInput,
        termsRow,
        buttonsRow, 
        pad,pad,pad,
        status
    );

    root.add(title, subtitle, form);
    window.add(root);

    window.run();
}
