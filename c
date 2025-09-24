<!DOCTYPE html>
<html lang="pl">
<head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>Zaawansowany Czat Globalny</title>
    <style>
        /* Reset i podstawy */
        * {
            box-sizing: border-box;
        }
        body {
            margin: 0; padding: 0;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #1a2a6c, #b21f1f, #fdbb2d);
            color: #eee;
            height: 100vh;
            display: flex;
            flex-direction: column;
        }

        header {
            background: rgba(0,0,0,0.7);
            padding: 15px;
            text-align: center;
            font-size: 24px;
            font-weight: bold;
            user-select: none;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }

        header h1 {
            margin: 0;
            font-size: 24px;
            flex-grow: 1;
        }

        .header-buttons {
            display: flex;
            gap: 10px;
        }

        main {
            flex: 1;
            display: flex;
            gap: 15px;
            padding: 15px;
        }

        /* Sidebar z użytkownikami online */
        #usersOnline {
            width: 220px;
            background: rgba(0,0,0,0.6);
            border-radius: 8px;
            padding: 10px;
            overflow-y: auto;
            display: flex;
            flex-direction: column;
        }
        #usersOnline h3 {
            margin-top: 0;
            margin-bottom: 10px;
            font-size: 20px;
            text-align: center;
        }
        #usersList {
            list-style: none;
            padding: 0;
            margin: 0;
            flex: 1;
        }
        #usersList li {
            padding: 6px 10px;
            margin-bottom: 5px;
            border-radius: 5px;
            cursor: pointer;
            background: rgba(255,255,255,0.1);
            transition: background-color 0.2s;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        #usersList li:hover {
            background: rgba(255,255,255,0.25);
        }
        #usersList li.selected {
            background: #28a745;
            color: white;
            font-weight: bold;
        }

        /* Sekcja czatu */
        #chatSection {
            flex: 1;
            display: flex;
            flex-direction: column;
            background: rgba(0,0,0,0.7);
            border-radius: 8px;
            padding: 10px;
        }

        #chatBox {
            flex: 1;
            overflow-y: auto;
            padding: 5px 10px;
            border-radius: 6px;
            background: #111;
            font-size: 14px;
        }

        /* Wiadomości */
        .message {
            margin-bottom: 10px;
            padding: 6px 10px;
            border-radius: 10px;
            max-width: 80%;
            word-wrap: break-word;
            position: relative;
        }
        .message.public {
            background: rgba(40,167,69,0.8);
            color: #e0f7e9;
        }
        .message.private {
            background: rgba(255,193,7,0.85);
            color: #4a3b00;
        }
        .message.admin-message {
            border: 2px solid #dc3545;
        }
        .message .meta {
            font-size: 11px;
            opacity: 0.7;
            margin-bottom: 3px;
        }
        .message .text {
            white-space: pre-wrap;
        }
        .message .deleteBtn {
            position: absolute;
            top: 6px;
            right: 6px;
            background: #dc3545;
            border: none;
            color: white;
            font-weight: bold;
            border-radius: 3px;
            cursor: pointer;
            padding: 2px 5px;
            font-size: 12px;
            display: none;
        }
        .message.admin-message .deleteBtn {
            display: block;
        }

        /* Formularz wysyłania */
        #sendForm {
            margin-top: 10px;
            display: flex;
            gap: 10px;
        }
        #msgInput {
            flex: 1;
            padding: 8px 12px;
            font-size: 16px;
            border-radius: 6px;
            border: none;
        }
        #sendBtn {
            background: #28a745;
            border: none;
            border-radius: 6px;
            padding: 8px 18px;
            color: white;
            font-size: 16px;
            cursor: pointer;
            transition: background-color 0.3s;
        }
        #sendBtn:hover {
            background: #218838;
        }

        /* Panel logowania/rejestracji */
        #authPanel {
            position: fixed;
            top:0; left:0; right:0; bottom:0;
            background: rgba(0,0,0,0.85);
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            z-index: 9999;
        }
        #authPanel form {
            background: #222;
            padding: 20px 25px;
            border-radius: 12px;
            min-width: 320px;
            box-shadow: 0 0 15px rgba(0,0,0,0.7);
        }
        #authPanel h2 {
            margin-top: 0;
            margin-bottom: 15px;
            color: #28a745;
            text-align: center;
        }
        #authPanel label {
            display: block;
            margin-bottom: 8px;
            font-weight: bold;
        }
        #authPanel input {
            width: 100%;
            padding: 8px 10px;
            margin-bottom: 15px;
            border-radius: 6px;
            border: none;
            font-size: 14px;
        }
        #authPanel button {
            width: 100%;
            padding: 10px;
            font-size: 16px;
            background: #28a745;
            border: none;
            border-radius: 6px;
            color: white;
            cursor: pointer;
            transition: background-color 0.3s;
        }
        #authPanel button:hover {
            background: #218838;
        }
        #authSwitch {
            margin-top: 10px;
            text-align: center;
            color: #bbb;
            cursor: pointer;
            user-select: none;
        }
        #authError {
            color: #dc3545;
            margin-bottom: 10px;
            font-weight: bold;
            min-height: 20px;
        }

        /* Wyświetlanie info o aktualnym userze */
        #userInfo {
            text-align: right;
            padding: 10px 15px;
            font-weight: bold;
            background: rgba(0,0,0,0.6);
            display: flex;
            justify-content: space-between;
            align-items: center;
            border-radius: 6px;
            margin-bottom: 10px;
        }
        #logoutBtn, #adminPanelBtn {
            background: #dc3545;
            border: none;
            color: white;
            padding: 5px 10px;
            border-radius: 6px;
            cursor: pointer;
            margin-left: 15px;
        }
        #logoutBtn:hover, #adminPanelBtn:hover {
            background: #b02a37;
        }
        #adminPanelBtn {
            background: #007bff;
        }
        #adminPanelBtn:hover {
            background: #0056b3;
        }

        /* Panel administracyjny */
        #adminPanel {
            position: fixed;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            background: #222;
            padding: 20px;
            border-radius: 12px;
            box-shadow: 0 0 20px rgba(0,0,0,0.8);
            z-index: 10000;
            min-width: 400px;
            display: none;
        }
        #adminPanel h2 {
            margin-top: 0;
            color: #fff;
            text-align: center;
        }
        #adminPanel .panel-sections {
            display: flex;
            flex-direction: column;
            gap: 20px;
        }
        #adminPanel .panel-section {
            background: #333;
            padding: 15px;
            border-radius: 8px;
        }
        #adminPanel h3 {
            margin-top: 0;
            color: #28a745;
        }
        #adminPanel .action-group {
            display: flex;
            flex-wrap: wrap;
            gap: 10px;
            align-items: center;
        }
        #adminPanel select {
            flex: 1;
            padding: 8px;
            border-radius: 6px;
            border: 1px solid #555;
            background-color: #444;
            color: white;
        }
        #adminPanel button {
            padding: 8px 12px;
            border: none;
            border-radius: 6px;
            cursor: pointer;
            color: white;
        }
        #adminPanel .btn-danger {
            background: #dc3545;
        }
        #adminPanel .btn-danger:hover {
            background: #b02a37;
        }
        #adminPanel .btn-warning {
            background: #ffc107;
            color: #212529;
        }
        #adminPanel .btn-warning:hover {
            background: #e0a800;
        }
        #adminPanel .btn-success {
            background: #28a745;
        }
        #adminPanel .btn-success:hover {
            background: #218838;
        }
        #adminPanel .close-btn {
            margin-top: 20px;
            background: #6c757d;
        }
        #adminPanel .close-btn:hover {
            background: #5a6268;
        }

        /* Responsywność */
        @media(max-width: 600px) {
            main {
                flex-direction: column;
            }
            #usersOnline {
                width: 100%;
                max-height: 150px;
                order: 2;
            }
            #chatSection {
                order: 1;
                height: 400px;
            }
        }
    </style>
</head>
<body>

<header>
    <h1>💬 Zaawansowany Czat Globalny</h1>
    <div class="header-buttons">
        <button id="adminPanelBtn" style="display:none;">Panel Admina</button>
        <button id="logoutBtn" style="display:none;">Wyloguj</button>
    </div>
</header>

<div id="authPanel">
    <form id="authForm">
        <h2 id="authTitle">Logowanie</h2>
        <div id="authError"></div>
        <label for="nickInput">Nick</label>
        <input type="text" id="nickInput" autocomplete="off" required minlength="3" maxlength="20" />
        <label for="passInput">Hasło</label>
        <input type="password" id="passInput" required minlength="6" maxlength="30" autocomplete="off" />
        <button type="submit" id="authSubmit">Zaloguj się</button>
        <div id="authSwitch">Nie masz konta? <strong>Zarejestruj się</strong></div>
    </form>
</div>

<main style="display:none;">
    <aside id="usersOnline">
        <h3>Użytkownicy Online</h3>
        <ul id="usersList"></ul>
    </aside>

    <section id="chatSection">
        <div id="userInfo">
            <div>
                <span id="currentUserNick"></span> (<span id="currentUserRole"></span>)
                <span id="chatModeIndicator" style="font-weight:normal; font-style:italic;"></span>
            </div>
            <button id="publicChatBtn" style="display:none;">Przejdź do czatu publicznego</button>
        </div>

        <div id="chatBox" aria-live="polite" aria-label="Okno czatu"></div>

        <form id="sendForm" autocomplete="off">
            <input type="text" id="msgInput" placeholder="Napisz wiadomość..." autocomplete="off" />
            <button type="submit" id="sendBtn">Wyślij</button>
        </form>
    </section>
</main>

<div id="adminPanel">
    <h2>Panel Administracyjny</h2>
    <div class="panel-sections">
        <div class="panel-section">
            <h3>Zarządzanie Użytkownikami</h3>
            <div class="action-group">
                <select id="userActionSelect">
                    <option value="">Wybierz użytkownika...</option>
                </select>
                <button id="kickUserBtn" class="btn-warning">Wyrzuć</button>
                <button id="banUserBtn" class="btn-danger">Banuj</button>
                <button id="muteUserBtn" class="btn-warning">Wycisz</button>
                <button id="unmuteUserBtn" class="btn-success">Odcisz</button>
                <button id="unbanUserBtn" class="btn-success">Odbanuj</button>
            </div>
        </div>

        <div class="panel-section">
            <h3>Zarządzanie Wiadomościami</h3>
            <div class="action-group">
                <button id="deleteAllPublicBtn" class="btn-danger">Usuń wszystkie wiadomości publiczne</button>
                <button id="deleteAllPrivateBtn" class="btn-danger">Usuń wszystkie wiadomości prywatne</button>
            </div>
        </div>
    </div>
    <button id="closeAdminPanel" class="close-btn">Zamknij</button>
</div>

<script type="module">
    import { initializeApp } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-app.js";
    import { getDatabase, ref, push, onValue, set, remove, onDisconnect, get, update } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-database.js";

    // Blokada podglądu źródła kodu
    document.addEventListener('contextmenu', event => event.preventDefault());
    document.addEventListener('keydown', event => {
        if (event.ctrlKey && (event.key === 'u' || event.key === 's')) {
            event.preventDefault();
        }
        if (event.key === 'F12') {
            event.preventDefault();
        }
    });

    // Firebase config — zastąp swoimi danymi!
    const firebaseConfig = {
        apiKey: "IzaSyBWtZUr7xoa31uoH18hksqSjCXMd2F18Ew",
        authDomain: "strona-f0d19.firebaseapp.com",
        databaseURL: "https://strona-f0d19-default-rtdb.firebaseio.com",
        projectId: "strona-f0d19",
        storageBucket: "strona-f0d19.appspot.com",
        messagingSenderId: "34203329400",
        appId: "1:34203329400:web:c934bf311b1a6701e8d",
        measurementId: "G-HYCP5F1J3E"
    };

    const app = initializeApp(firebaseConfig);
    const db = getDatabase(app);

    // Nowa funkcja do pobierania adresu IP
    async function getClientIp() {
        try {
            const response = await fetch('https://api.ipify.org?format=json');
            const data = await response.json();
            return data.ip;
        } catch (error) {
            console.error('Błąd podczas pobierania IP:', error);
            return null;
        }
    }

    // Pomocnik hashujący SHA-256 (prosty)
    async function hashPassword(pass) {
        const encoder = new TextEncoder();
        const data = encoder.encode(pass);
        const hashBuffer = await crypto.subtle.digest('SHA-256', data);
        const hashArray = Array.from(new Uint8Array(hashBuffer));
        return hashArray.map(b => b.toString(16).padStart(2, '0')).join('');
    }

    // UI elementy
    const authPanel = document.getElementById('authPanel');
    const authForm = document.getElementById('authForm');
    const authTitle = document.getElementById('authTitle');
    const authError = document.getElementById('authError');
    const authSwitch = document.getElementById('authSwitch');
    const nickInput = document.getElementById('nickInput');
    const passInput = document.getElementById('passInput');
    const mainContent = document.querySelector('main');
    const usersListEl = document.getElementById('usersList');
    const chatBox = document.getElementById('chatBox');
    const msgInput = document.getElementById('msgInput');
    const sendForm = document.getElementById('sendForm');
    const currentUserNickEl = document.getElementById('currentUserNick');
    const currentUserRoleEl = document.getElementById('currentUserRole');
    const chatModeIndicator = document.getElementById('chatModeIndicator');
    const logoutBtn = document.getElementById('logoutBtn');
    const adminPanelBtn = document.getElementById('adminPanelBtn');
    const publicChatBtn = document.getElementById('publicChatBtn');

    // Panel administracyjny
    const adminPanel = document.getElementById('adminPanel');
    const deleteAllPublicBtn = document.getElementById('deleteAllPublicBtn');
    const deleteAllPrivateBtn = document.getElementById('deleteAllPrivateBtn');
    const closeAdminPanelBtn = document.getElementById('closeAdminPanel');
    const userActionSelect = document.getElementById('userActionSelect');
    const kickUserBtn = document.getElementById('kickUserBtn');
    const banUserBtn = document.getElementById('banUserBtn');
    const muteUserBtn = document.getElementById('muteUserBtn');
    const unbanUserBtn = document.getElementById('unbanUserBtn');
    const unmuteUserBtn = document.getElementById('unmuteUserBtn');
    
    let currentUser = null; 
    let selectedUser = null; 
    let isRegisterMode = false;
    let messageListeners = [];
    let isMuted = false;
    let isBanned = false;
    let lastMessageTimestamp = 0;
    const spamInterval = 2000; // 2 sekundy
    let clientIp = null;

    function formatDate(ts) {
        const d = new Date(ts);
        return d.toLocaleString('pl-PL', { day: '2-digit', month: '2-digit', year: 'numeric', hour:'2-digit', minute:'2-digit' });
    }

    function escapeHtml(text) {
        const div = document.createElement('div');
        div.textContent = text;
        return div.innerHTML;
    }

    function scrollToBottom() {
        chatBox.scrollTop = chatBox.scrollHeight;
    }

    function renderMessages(messagesSnapshot) {
        const isAtBottom = chatBox.scrollHeight - chatBox.clientHeight <= chatBox.scrollTop + 1;
        chatBox.innerHTML = '';
        const messages = [];

        messagesSnapshot.forEach(msgSnap => {
            const msg = msgSnap.val();
            const messageData = { key: msgSnap.key, ...msg };
            if (msg.to) {
                const sortedPair = [msg.user, msg.to].sort();
                messageData.conversationKey = `${sortedPair[0]}_${sortedPair[1]}`;
            }
            messages.push(messageData);
        });

        messages.sort((a, b) => a.timestamp - b.timestamp);

        messages.forEach(msg => {
            const div = document.createElement('div');
            div.classList.add('message');
            
            if(msg.to) div.classList.add('private');
            else div.classList.add('public');

            if(currentUser.isAdmin) div.classList.add('admin-message');

            const fromUser = msg.user === currentUser.nick ? 'Ja' : `<b>${escapeHtml(msg.user)}</b>`;
            const toUser = msg.to ? `→ <b>${escapeHtml(msg.to)}</b>` : '';

            div.innerHTML = `
                <div class="meta">${fromUser} ${toUser} <span> - ${formatDate(msg.timestamp)}</span></div>
                <div class="text">${escapeHtml(msg.text)}</div>
            `;

            if(currentUser.isAdmin) {
                const delBtn = document.createElement('button');
                delBtn.className = 'deleteBtn';
                delBtn.textContent = 'Usuń';
                delBtn.addEventListener('click', async () => {
                    if(confirm('Na pewno usunąć tę wiadomość?')) {
                        const messageRef = msg.to ? ref(db, `messages_private/${msg.conversationKey}/${msg.key}`) : ref(db, 'messages/' + msg.key);
                        await remove(messageRef);
                    }
                });
                div.appendChild(delBtn);
            }
            chatBox.appendChild(div);
        });

        if (isAtBottom) {
            scrollToBottom();
        }
    }

    function removeAllListeners() {
        messageListeners.forEach(listener => listener());
        messageListeners = [];
    }

    function listenForMessages() {
        removeAllListeners();
        const messagesRef = selectedUser === 'public' ? ref(db, 'messages') : (selectedUser ? ref(db, `messages_private/${[currentUser.nick, selectedUser].sort().join('_')}`) : null);

        if (messagesRef) {
            const unsubscribe = onValue(messagesRef, (snapshot) => {
                if(!currentUser) return;
                renderMessages(snapshot);
            });
            messageListeners.push(unsubscribe);
        } else {
            chatBox.innerHTML = '';
        }
    }

    function switchChatMode(mode, targetUser = null) {
        selectedUser = targetUser;
        let selectedLi = document.querySelector('#usersList li.selected');
        if (selectedLi) selectedLi.classList.remove('selected');

        if (mode === 'public') {
            selectedUser = 'public';
            chatModeIndicator.textContent = '(czat publiczny)';
            publicChatBtn.style.display = 'none';
        } else {
            chatModeIndicator.textContent = `(DM: ${selectedUser})`;
            publicChatBtn.style.display = 'inline-block';
            const userLi = document.querySelector(`#usersList li[data-nick="${targetUser}"]`);
            if (userLi) userLi.classList.add('selected');
        }
        listenForMessages();
    }

    async function updateAdminUserList() {
        const usersRef = ref(db, 'users');
        const usersSnapshot = await get(usersRef);
        userActionSelect.innerHTML = `<option value="">Wybierz użytkownika...</option>`;
        if (usersSnapshot.exists()) {
            usersSnapshot.forEach(userSnap => {
                const nick = userSnap.key;
                if (nick !== currentUser?.nick) {
                    const status = userSnap.val().status || {};
                    const isBanned = status.isBanned || false;
                    const isMuted = status.isMuted || false;
                    
                    const option = document.createElement('option');
                    option.value = nick;
                    option.textContent = nick;
                    if (isBanned) option.textContent += ' (ZBANOWANY)';
                    if (isMuted) option.textContent += ' (WYCISZONY)';
                    userActionSelect.appendChild(option);
                }
            });
        }
    }

    const onlineRef = ref(db, 'online');
    onValue(onlineRef, (snapshot) => {
        usersListEl.innerHTML = '';
        snapshot.forEach(userSnap => {
            const nick = userSnap.key;
            if (nick !== currentUser?.nick) {
                const li = document.createElement('li');
                li.textContent = nick;
                li.setAttribute('data-nick', nick);
                if(selectedUser === nick) li.classList.add('selected');
                li.title = `Kliknij, by wysłać wiadomość do ${nick}`;
                li.addEventListener('click', () => {
                    switchChatMode('private', nick);
                });
                usersListEl.appendChild(li);
            }
        });
    });

    async function afterLogin() {
        authPanel.style.display = 'none';
        mainContent.style.display = 'flex';
        logoutBtn.style.display = 'inline-block';
        currentUserNickEl.textContent = currentUser.nick;
        currentUserRoleEl.textContent = currentUser.isAdmin ? 'Admin' : 'Użytkownik';
        if (currentUser.isAdmin) {
            adminPanelBtn.style.display = 'inline-block';
        }

        const userStatusRef = ref(db, `users/${currentUser.nick}/status`);
        const statusSnap = await get(userStatusRef);
        if(statusSnap.exists()) {
            const status = statusSnap.val();
            isBanned = status.isBanned || false;
            isMuted = status.isMuted || false;
        }

        if (isBanned) {
            alert('Twoje konto zostało zbanowane.');
            logoutBtn.click();
            return;
        }

        msgInput.disabled = isMuted;
        msgInput.placeholder = isMuted ? 'Jesteś wyciszony i nie możesz pisać.' : 'Napisz wiadomość...';

        const userOnlineRef = ref(db, 'online/' + currentUser.nick);
        set(userOnlineRef, true);
        onDisconnect(userOnlineRef).remove();

        switchChatMode('public');
    }

    authForm.addEventListener('submit', async (e) => {
        e.preventDefault();
        authError.textContent = '';
        const nick = nickInput.value.trim();
        const pass = passInput.value;
        
        clientIp = await getClientIp();
        if (!clientIp) {
            authError.textContent = 'Błąd: Nie można pobrać adresu IP. Spróbuj ponownie.';
            return;
        }

        const bannedIpsRef = ref(db, 'banned_ips/' + clientIp.replace(/\./g, '_'));
        const bannedIpSnap = await get(bannedIpsRef);
        if (bannedIpSnap.exists()) {
            authError.textContent = 'Twój adres IP jest zbanowany.';
            return;
        }

        if(nick.length < 3 || pass.length < 6) {
            authError.textContent = 'Nick musi mieć min. 3 znaki, hasło min. 6 znaków.';
            return;
        }

        const userRef = ref(db, 'users/' + nick);
        const snapshot = await get(userRef);

        if(isRegisterMode) {
            const usersWithSameIpRef = ref(db, 'users');
            const usersWithSameIpSnapshot = await get(usersWithSameIpRef);
            let ipCount = 0;
            if (usersWithSameIpSnapshot.exists()) {
                usersWithSameIpSnapshot.forEach(userSnap => {
                    const userData = userSnap.val();
                    if (userData.ip === clientIp) {
                        ipCount++;
                    }
                });
            }
            if (ipCount >= 1) { // Limit 1 konta na IP
                authError.textContent = 'Możesz mieć tylko jedno konto z tego adresu IP.';
                return;
            }

            if(snapshot.exists()) {
                authError.textContent = 'Ten nick jest już zajęty.';
                return;
            }
            const hashed = await hashPassword(pass);
            await set(userRef, { passwordHash: hashed, isAdmin: false, ip: clientIp });
            currentUser = { nick, isAdmin: false };
            afterLogin();
        } else {
            if(!snapshot.exists()) {
                authError.textContent = 'Nie znaleziono takiego nicku.';
                return;
            }
            const data = snapshot.val();
            if (data.status?.isBanned) {
                authError.textContent = 'Twoje konto zostało zbanowane.';
                return;
            }
            const hashed = await hashPassword(pass);
            if(hashed !== data.passwordHash) {
                authError.textContent = 'Niepoprawne hasło.';
                return;
            }
            currentUser = { nick, isAdmin: data.isAdmin || false };
            afterLogin();
        }
    });

    authSwitch.addEventListener('click', () => {
        isRegisterMode = !isRegisterMode;
        authTitle.textContent = isRegisterMode ? 'Rejestracja' : 'Logowanie';
        authSubmit.textContent = isRegisterMode ? 'Zarejestruj się' : 'Zaloguj się';
        authError.textContent = '';
        authSwitch.innerHTML = isRegisterMode ?
            'Masz konto? <strong>Zaloguj się</strong>' :
            'Nie masz konta? <strong>Zarejestruj się</strong>';
    });

    logoutBtn.addEventListener('click', () => {
        if(currentUser) {
            remove(ref(db, 'online/' + currentUser.nick));
        }
        currentUser = null;
        selectedUser = null;
        mainContent.style.display = 'none';
        logoutBtn.style.display = 'none';
        adminPanelBtn.style.display = 'none';
        authPanel.style.display = 'flex';
        authForm.reset();
        removeAllListeners();
    });

    publicChatBtn.addEventListener('click', () => {
        switchChatMode('public');
    });

    sendForm.addEventListener('submit', async (e) => {
        e.preventDefault();
        if(!currentUser || isMuted) return;
        const now = Date.now();
        if (now - lastMessageTimestamp < spamInterval) {
            authError.textContent = 'Spam! Poczekaj 2 sekundy przed wysłaniem kolejnej wiadomości.';
            return;
        }
        let text = msgInput.value.trim();
        if(text.length === 0) return;

        const timestamp = now;
        const msgObject = {
            user: currentUser.nick,
            text,
            timestamp
        };

        if(selectedUser !== 'public') {
            const sortedPair = [currentUser.nick, selectedUser].sort();
            const privatePath = `messages_private/${sortedPair[0]}_${sortedPair[1]}`;
            msgObject.to = selectedUser;
            await push(ref(db, privatePath), msgObject);
        } else {
            await push(ref(db, 'messages'), msgObject);
        }
        msgInput.value = '';
        lastMessageTimestamp = now;
    });

    adminPanelBtn.addEventListener('click', () => {
        adminPanel.style.display = 'block';
        updateAdminUserList();
    });

    closeAdminPanelBtn.addEventListener('click', () => {
        adminPanel.style.display = 'none';
    });
    
    kickUserBtn.addEventListener('click', async () => {
        const userToKick = userActionSelect.value;
        if (!userToKick) {
            alert('Wybierz użytkownika do wyrzucenia.');
            return;
        }
        if (confirm(`Na pewno chcesz wyrzucić użytkownika ${userToKick}?`)) {
            await remove(ref(db, `online/${userToKick}`));
            alert(`Użytkownik ${userToKick} został wyrzucony.`);
            updateAdminUserList();
            adminPanel.style.display = 'none';
        }
    });

    deleteAllPublicBtn.addEventListener('click', async () => {
        if(confirm('Jesteś pewien, że chcesz usunąć WSZYSTKIE wiadomości publiczne? Tej operacji nie można cofnąć!')) {
            await remove(ref(db, 'messages'));
            alert('Wszystkie wiadomości publiczne zostały usunięte.');
            adminPanel.style.display = 'none';
        }
    });

    deleteAllPrivateBtn.addEventListener('click', async () => {
        if(confirm('Jesteś pewien, że chcesz usunąć WSZYSTKIE wiadomości prywatne? Tej operacji nie można cofnąć!')) {
            await remove(ref(db, 'messages_private'));
            alert('Wszystkie wiadomości prywatne zostały usunięte.');
            adminPanel.style.display = 'none';
        }
    });

    banUserBtn.addEventListener('click', async () => {
        const userToBan = userActionSelect.value;
        if (!userToBan) {
            alert('Wybierz użytkownika do zbanowania.');
            return;
        }
        if (confirm(`Na pewno chcesz zbanować użytkownika ${userToBan}?`)) {
            const userRef = ref(db, `users/${userToBan}`);
            const userSnap = await get(userRef);
            if(userSnap.exists()){
                const userIp = userSnap.val().ip;
                if(userIp) {
                    await set(ref(db, 'banned_ips/' + userIp.replace(/\./g, '_')), true);
                }
            }
            await update(ref(db, `users/${userToBan}/status`), { isBanned: true });
            await remove(ref(db, `online/${userToBan}`));
            alert(`Użytkownik ${userToBan} oraz jego adres IP zostały zbanowane.`);
            updateAdminUserList(); 
            adminPanel.style.display = 'none';
        }
    });

    muteUserBtn.addEventListener('click', async () => {
        const userToMute = userActionSelect.value;
        if (!userToMute) {
            alert('Wybierz użytkownika do wyciszenia.');
            return;
        }
        if (confirm(`Na pewno chcesz wyciszyć użytkownika ${userToMute}?`)) {
            const userRef = ref(db, `users/${userToMute}/status`);
            await update(userRef, { isMuted: true });
            alert(`Użytkownik ${userToMute} został wyciszony.`);
            updateAdminUserList(); 
            adminPanel.style.display = 'none';
        }
    });

    unmuteUserBtn.addEventListener('click', async () => {
        const userToUnmute = userActionSelect.value;
        if (!userToUnmute) {
            alert('Wybierz użytkownika do odciszenia.');
            return;
        }
        if (confirm(`Na pewno chcesz odciszyć użytkownika ${userToUnmute}?`)) {
            const userRef = ref(db, `users/${userToUnmute}/status`);
            await update(userRef, { isMuted: false });
            alert(`Użytkownik ${userToUnmute} został odciszony.`);
            updateAdminUserList();
            adminPanel.style.display = 'none';
        }
    });

    unbanUserBtn.addEventListener('click', async () => {
        const userToUnban = userActionSelect.value;
        if (!userToUnban) {
            alert('Wybierz użytkownika do odbanowania.');
            return;
        }
        if (confirm(`Na pewno chcesz odbanować użytkownika ${userToUnban}?`)) {
            const userRef = ref(db, `users/${userToUnban}`);
            const userSnap = await get(userRef);
            if(userSnap.exists()){
                const userIp = userSnap.val().ip;
                if(userIp) {
                    await remove(ref(db, 'banned_ips/' + userIp.replace(/\./g, '_')));
                }
            }
            await update(ref(db, `users/${userToUnban}/status`), { isBanned: false });
            alert(`Użytkownik ${userToUnban} został odbanowany.`);
            updateAdminUserList(); 
            adminPanel.style.display = 'none';
        }
    });

</script>
<script src="protect.js"></script>
</body>
</html>

