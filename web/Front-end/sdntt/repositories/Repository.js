import Cookies from "js-cookie";
import axios from "axios";

const token = Cookies.get("id_token");
const baseDomain = "http://127.0.0.1:8000/api";

export const customHeaders = {
    "Content-Type": "multipart/form-data",
    Accept: "application/json",
};
export const apiTT = `${baseDomain}`;

export default axios.create({
    apiTT,
    headers: customHeaders,
});

// export const serializeQuery = (query) => {
//     return Object.keys(query)
//         .map(
//         (key) => `${encodeURIComponent(key)}=${encodeURIComponent(query[key])}`
//         )
//         .join("&");
// };